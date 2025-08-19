/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:46:36 by leothoma          #+#    #+#             */
/*   Updated: 2025/08/07 18:48:20 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eating(t_philo *philo)
{
	if (its_over(philo))
		return ;
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_printf(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->right_fork);
		safe_printf(philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!its_over(philo))
			safe_printf(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->left_fork);
		if (!its_over(philo))
			safe_printf(philo, "has taken a fork", 0);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->n_eat++;
	pthread_mutex_unlock(&philo->meal_mutex);
	smart_sleep(philo, philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	if (its_over(philo))
		return ;
	safe_printf(philo, "is sleeping", 0);
	smart_sleep(philo, philo->args->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	if (its_over(philo))
		return ;
	safe_printf(philo, "is thinking", 0);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->index % 2 == 0)
		usleep((philo->index % 2) * 1000);
	while (!its_over(philo))
	{
		if (its_over(philo))
			break ;
		eating(philo);
		if (its_over(philo))
			break ;
		sleeping(philo);
		if (its_over(philo))
			break ;
		thinking(philo);
		if (its_over(philo))
			break ;
		usleep(500);
	}
	return (NULL);
}

void	*monitoring_routine(void *arg)
{
	t_philo	*philos;
	t_args	*args;
	size_t	i;
	long	now;

	philos = (t_philo *)arg;
	args = philos[0].args;
	while (1)
	{
		i = -1;
		while (++i < philos[0].n)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			now = get_time();
			if (now - philos[i].last_meal_time > args->time_to_die)
				return (norme_helper(&philos[i], args), NULL);
			pthread_mutex_unlock(&philos[i].meal_mutex);
			if (args->n_eat != -1 && try_end(philos, args))
				return (args->simulation_stopped = 1, NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

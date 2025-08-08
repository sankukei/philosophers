/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:46:22 by leothoma          #+#    #+#             */
/*   Updated: 2025/08/07 18:48:43 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	smart_sleep(t_philo *philo, long duration_ms)
{
	long	start;

	start = get_time();
	while (!its_over(philo))
	{
		if (get_time() - start >= duration_ms)
			break ;
		usleep(1000);
	}
}

int	its_over(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->args->stop_mutex);
	stopped = philo->args->simulation_stopped;
	pthread_mutex_unlock(&philo->args->stop_mutex);
	return (stopped);
}

int	its_over_old(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (philo->args->simulation_stopped == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->stop_mutex);
	return (0);
}

void	safe_printf(t_philo *philo, const char *msg, int force)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->stop_mutex);
	pthread_mutex_lock(&args->printf_mutex);
	if (args->simulation_stopped && !force)
	{
		pthread_mutex_unlock(&args->printf_mutex);
		pthread_mutex_unlock(&args->stop_mutex);
		return ;
	}
	printf("%ld %d %s\n", get_time() - args->start_time, philo->index, msg);
	pthread_mutex_unlock(&args->printf_mutex);
	pthread_mutex_unlock(&args->stop_mutex);
}

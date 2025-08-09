/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:46:46 by leothoma          #+#    #+#             */
/*   Updated: 2025/08/07 18:46:47 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	destroy_mutexes(size_t n, t_mut *mutex)
{
	size_t	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&mutex->forks[i++]);
	free(mutex->forks);
}

int	init_mutexes(size_t n, t_mut *mutex)
{
	size_t	i;

	i = 0;
	mutex->forks = malloc(n * sizeof(pthread_mutex_t));
	if (!mutex->forks)
		return (0);
	while (i < n)
	{
		if (pthread_mutex_init(&mutex->forks[i++], NULL) != 0)
		{
			printf("mutex init failed");
			while (i > 0)
				pthread_mutex_destroy(&mutex->forks[--i]);
			free(mutex->forks);
			return (0);
		}
	}
	return (1);
}

t_philo	*init_philos(size_t n, t_args *args, t_mut *mutex)
{
	size_t	i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < n)
	{
		philos[i].n = n;
		philos[i].index = i + 1;
		philos[i].args = args;
		philos[i].left_fork = &mutex->forks[i];
		philos[i].right_fork = &mutex->forks[(i + 1) % n];
		philos[i].last_meal_time = args->start_time;
		philos[i].n_eat = 0;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	return (philos);
}

int	init_threads(size_t n, t_philo *philos)
{
	size_t		i;
	pthread_t	*thread_index;

	i = 0;
	thread_index = malloc(sizeof(pthread_t) * (n + 1));
	while (i < n)
	{
		if (pthread_create(&thread_index[i], NULL,
				(void *)philo_routine, &philos[i]))
		{
			printf("pthread_create failed\n");
			return (0);
		}
		i++;
	}
	pthread_create(&thread_index[i++], NULL, monitoring_routine, philos);
	i = 0;
	while (i < n)
		pthread_join(thread_index[i++], NULL);
	free(thread_index);
	return (1);
}

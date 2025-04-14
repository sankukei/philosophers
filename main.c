/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:24:52 by leothoma          #+#    #+#             */
/*   Updated: 2025/04/08 13:24:52 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	am_i_dead(t_philo *philo)
{
	int	i;

	i = 0;
	if (i == 0)
		return (1);
	return (0);
}

void	*routine(void *args)
{
	t_philo *philo = args;
	while (1)
	{
		if (am_i_dead(philo))
		{
			printf("philo %d has died\n", philo->index);
			break;
		}
		usleep(1);
	}
	return (0);
}

int	init_philos(size_t n, t_philo **philos, t_args *args, t_mut *forks)
{
	size_t	i;

	i = 0;
	t_philo	*tmp;
	*philos = malloc(n * sizeof(t_philo));

	tmp = *philos;
	while (i < n)
	{
		(*philos)->index = i;
		(*philos)->args = args;
		(*philos)->forks = forks;
		(*philos)++;
		i++;
	}
	*philos = tmp;
	return (1);
}

int	init_mutexes(size_t n, t_mut **mutexx)
{
	size_t	i;

	*mutexx = malloc(sizeof(t_mut));
	(*mutexx)->forks = malloc(n * sizeof(pthread_mutex_t));
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&(*mutexx)->forks[i++], NULL) != 0)
		{
		//	check if function return -1; if so call a function to destroy all other mutexes	
			write(1, "prankex\n", 8);
			return (0);
		}
	}
	return (1);
}

int	init_threads(int n_philo, t_philo *philo)
{
	int	i;

	pthread_t	*thread_index;
	i = 0;
	thread_index = malloc(n_philo * sizeof(pthread_t));
	if (!thread_index)
		return (0);
	while (i < n_philo)
	{
		if (pthread_create(&thread_index[i++], NULL, routine, philo) != 0)
		{
			write(1, "pranked\n", 7);
			return (0);
		}
		philo++;
	}
	i = 0;
	while (i < n_philo)
		pthread_join(thread_index[i++], NULL);
	return (1);
}

void	init_args(char **av, int ac, t_args **args)
{
	(*args)->n_philo = ft_atoi(av[1]);
	(*args)->time_to_die = ft_atoi(av[2]);
	(*args)->time_to_eat = ft_atoi(av[3]);
	(*args)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*args)->n_eat = ft_atoi(av[5]);
}

void	_start_(size_t n_philo, t_args *args, t_mut **mutex, t_philo **philos)
{
	init_mutexes(n_philo, mutex);
	init_philos(n_philo, philos, args, *mutex);
	init_threads(n_philo, *philos);
}

int	check_parsing(char **av)
{
	int	i;
	int	y;
	int	temp;
	
	i = 1;
	y = 0;
	while (av[i])
	{
		while (av[i][y])
		{
			temp = ft_atoi(av[i]);
			if (temp == 0)
				return (0);
			if (!(av[i][y] <= '9' && av[i][y] >= '0'))
				return (0);
			y++;
		}
		y = 0;
		i++;
	}
	return (1);
}

void	print_error(int	code)
{
	if (code == 1)
		write(1, "./philo + n_philo + time_to_die + time_to_eat + time_to_sleep\n", 62);
}

int	main(int ac, char **av)
{
	t_args	*args;
	t_mut	*mutex;
	t_philo  *philos;

	args = malloc(sizeof(t_args));
	if ((ac == 5 || ac == 6) && check_parsing(av))
	{
		init_args(av, ac, &args);
		_start_(args->n_philo, args, &mutex, &philos);
	}
	else
	{
		print_error(1);
		return (0);
	}
}

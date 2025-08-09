/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:46:42 by leothoma          #+#    #+#             */
/*   Updated: 2025/08/07 18:46:42 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	start(size_t n, t_args *args)
{
	t_philo	*philos;
	t_mut	mutex;

	args->start_time = get_time();
	philos = NULL;
	if (!init_mutexes(n, &mutex))
		return ;
	philos = init_philos(n, args, &mutex);
	if (!philos)
		return ;
	init_threads(n, philos);
	free(philos);
	destroy_mutexes(n, &mutex);
}

void	init_args(char **av, int ac, t_args *args)
{
	args->n_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->simulation_stopped = 0;
	pthread_mutex_init(&args->stop_mutex, NULL);
	pthread_mutex_init(&args->printf_mutex, NULL);
	if (ac == 6)
		args->n_eat = ft_atoi(av[5]);
	else
		args->n_eat = -1;
}

// TODO implementer le dernier argument n_eat

int	main(int ac, char **av)
{
	t_args	args;

	if ((ac == 5 || ac == 6) && check_parsing(av))
	{
		init_args(av, ac, &args);
		start(args.n_philo, &args);
	}
	else
		printf("parsing error\n");
	return (EXIT_SUCCESS);
}

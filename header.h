/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:24:58 by leothoma          #+#    #+#             */
/*   Updated: 2025/04/08 13:24:58 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
} t_mut;

typedef	struct s_time
{
	size_t	start_utime;
	size_t	start_stime;
	size_t	elapsed;
} t_time;

typedef struct s_args
{
	size_t	n_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	n_eat;
}	t_args;

typedef struct s_philo
{
	int	index;
	int	is_sleeping;
	int	is_thinking;
	int	is_eating;
	int	has_eaten;
	int	is_dead;
	t_mut	*forks;
	t_args	*args;
	t_time	*time;
	//t_all_philos	*all_philos;
}	t_philo;

size_t	ft_atoi(const char *str);

#endif

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
}	t_mut;

typedef struct s_time
{
	size_t	start_utime;
	size_t	start_stime;
	size_t	elapsed;
}	t_time;

typedef struct s_args
{
	long				n_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				n_eat;
	int					simulation_stopped;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		printf_mutex;
	long				start_time;
}	t_args;

typedef struct s_philo
{
	int					index;
	int					is_sleeping;
	int					is_thinking;
	int					is_eating;
	int					has_eaten;
	int					is_dead;
	size_t				n;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
	long				last_meal_time;
	t_mut				*forks;
	t_args				*args;
	t_time				*time;
	//t_all_philos	*all_philos;
}	t_philo;

size_t	ft_atoi(const char *str);
long	get_time(void);
t_philo	*init_philos(size_t n, t_args *args, t_mut *mutex);
int		init_mutexes(size_t n, t_mut *mutex);
int		init_threads(size_t n, t_philo *philos);
void	*philo_routine(void *args);
void	destroy_mutexes(size_t n, t_mut *mutex);
void	*monitoring_routine(void *args);
void	smart_sleep(t_philo *philo, long duration_ms);
int		its_over(t_philo *philo);
void	safe_printf(t_philo *philo, const char *message, int death);
#endif

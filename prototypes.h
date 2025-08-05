#include "header.h"

t_philo	*init_philos(size_t n, t_args *args, t_mut *mutex);
int	init_mutexes(size_t n, t_mut *mutex);
int	init_threads(size_t n, t_philo *philos);
void	*philo_routine(void *args);
void    destroy_mutexes(size_t n, t_mut *mutex);

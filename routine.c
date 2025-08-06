#include "header.h"

void	print_status(int status, int index)
{
	if (status == 0)
		printf("philos %d has died\n", index);
}

int     its_over(t_philo *philo)
{
        pthread_mutex_lock(&philo->args->stop_mutex);
        if (philo->args->simulation_stopped == 1)
                return (1);
        pthread_mutex_unlock(&philo->args->stop_mutex);
        return (0);
}

void    smart_sleep(t_philo *philo, long duration_ms)
{
        long start;

        start = get_time();
        while (!its_over(philo))
        {
                if (get_time() - start >= duration_ms)
                        break;
                usleep(1000);
        }
}

void    eating(t_philo *philo)
{
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken a fork\n", get_time() - philo->args->start_time, philo->index);
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken a fork\n", get_time() - philo->args->start_time, philo->index);
        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal_time = get_time();
        pthread_mutex_unlock(&philo->meal_mutex);
        printf("%ld %d is eating\n", get_time() - philo->args->start_time, philo->index);
        smart_sleep(philo, philo->args->time_to_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

}

void    sleeping(t_philo *philo)
{
        printf("%ld %d is sleeping\n", get_time() - philo->args->start_time, philo->index);
        smart_sleep(philo, philo->args->time_to_sleep);

}

void    thinking(t_philo *philo)
{
        if (its_over(philo))
                return ;
	printf("%ld %d is thinking\n", get_time() - philo->args->start_time, philo->index);
}

void	*philo_routine(void *args)
{
	t_philo *philo = (t_philo *)args;


        if (philo->index % 2 == 0)
                usleep(500);
	while (!its_over(philo))
	{
                eating(philo);
                sleeping(philo);
                thinking(philo);
		usleep(500);
	}
	return (0);
}

void    *monitoring_routine(void *arg)
{
        t_philo *philos;
        t_args  *args;
        size_t  i;
        long    now;
        size_t  n;

        philos = (t_philo *)arg;
        args = philos[0].args;
        n = philos[0].n;
        while (1)
        {
                i = 0;
                while(i  < n)
                {
                        pthread_mutex_lock(&philos[i].meal_mutex); // set le mutex dans init
                        now = get_time();
                        if (now - philos[i].last_meal_time > args->time_to_die)
                        {
                                pthread_mutex_unlock(&args->meal_mutex);
                                pthread_mutex_lock(&args->stop_mutex);
                                args->simulation_stopped = 1;
                                pthread_mutex_unlock(&args->stop_mutex);
                                printf("%ld philo %d died\n", now - args->start_time, philos[i].index);
                                pthread_mutex_unlock(&philos[i].meal_mutex);
                                return (NULL);
                        }
                        pthread_mutex_unlock(&philos[i].meal_mutex);
                        i++;
                }
                usleep(1000);
        }
        return (NULL);
}

#include "header.h"

void    safe_printf(t_philo *philo, const char *message)
{
        pthread_mutex_lock(&philo->args->printf_mutex);
        printf("%ld %d %s\n", get_time() - philo->args->start_time, philo->index, message);
        pthread_mutex_unlock(&philo->args->printf_mutex);
}

int     its_over(t_philo *philo)
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
        if (its_over(philo))
                return ;
        if (philo->index % 2 == 0)
        {
                pthread_mutex_lock(philo->left_fork);
                safe_printf(philo, "has taken a fork");
                //printf("%ld %d has taken a fork\n", get_time() - philo->args->start_time, philo->index);
                pthread_mutex_lock(philo->right_fork);
                safe_printf(philo, "has taken a fork");
                //printf("%ld %d has taken a fork\n", get_time() - philo->args->start_time, philo->index);
        }
        else
        {
                pthread_mutex_lock(philo->right_fork);
                safe_printf(philo, "has taken a fork");
                //printf("%ld %d has taken a fork\n", get_time() - philo->args->start_time, philo->index);
                pthread_mutex_lock(philo->left_fork);
                safe_printf(philo, "has taken a fork");
                //printf("%ld %d has taken a fork\n", get_time() - philo->args->start_time, philo->index);
        }
        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal_time = get_time();
        pthread_mutex_unlock(&philo->meal_mutex);
        safe_printf(philo, "is eating");
        //printf("%ld %d is eating\n", get_time() - philo->args->start_time, philo->index);
        smart_sleep(philo, philo->args->time_to_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

}

void    sleeping(t_philo *philo)
{
        if (its_over(philo))
                return ;
        safe_printf(philo, "is sleeping");
        //printf("%ld %d is sleeping\n", get_time() - philo->args->start_time, philo->index);
        smart_sleep(philo, philo->args->time_to_sleep);

}

void    thinking(t_philo *philo)
{
        if (its_over(philo))
                return ;
        safe_printf(philo, "is thinking");
	//printf("%ld %d is thinking\n", get_time() - philo->args->start_time, philo->index);
        //smart_sleep(philo, 100);
}

void	*philo_routine(void *args)
{
	t_philo *philo = (t_philo *)args;


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
                                pthread_mutex_unlock(&philos[i].meal_mutex);
                                pthread_mutex_lock(&args->stop_mutex);
                                if (!args->simulation_stopped)
                                {
                                        args->simulation_stopped = 1;
                                        pthread_mutex_lock(&args->printf_mutex);
                                        printf("%ld philo %d died\n", now - args->start_time, philos[i].index);
                                        pthread_mutex_unlock(&args->printf_mutex);
                                }
                                pthread_mutex_unlock(&args->stop_mutex);
                                return (NULL);
                        }
                        pthread_mutex_unlock(&philos[i].meal_mutex);
                        i++;
                }
                usleep(1000);
        }
        return (NULL);
}

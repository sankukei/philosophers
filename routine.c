#include "header.h"

void	print_status(int status, int index)
{
	if (status == 0)
		printf("philos %d has died\n", index);
}

int	am_i_dead(size_t index)
{
	if (1)
		return (1);
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo *philos = (t_philo *)args;

	while (1)
	{
		if (am_i_dead(philos->index))
		{
			print_status(0, philos->index);
			break;
		}
		usleep(1);
	}
	return (0);
}

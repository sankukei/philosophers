/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 23:38:22 by leothoma          #+#    #+#             */
/*   Updated: 2025/08/08 23:38:28 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	monitoring_routine_helper(t_philo *philo, t_args *args)
{
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&args->stop_mutex);
	if (!args->simulation_stopped)
		args->simulation_stopped = 1;
	pthread_mutex_unlock(&args->stop_mutex);
	safe_printf(philo, "died", 1);
}

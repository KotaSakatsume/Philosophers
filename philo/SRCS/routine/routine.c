/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/11 19:09:47 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_stopped(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->stop_mutex);
	flag = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (flag);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (get_timestamp(philo->data) < 1)
		usleep(100);
	while (!is_simulation_stopped(philo->data))
	{
		take_forks(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		eat(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		ft_sleep(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		think(philo);
	}
	return (NULL);
}

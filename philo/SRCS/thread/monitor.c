/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/11 19:23:41 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

static int	check_philosopher_death(t_philosopher *philo, t_data *data, int i)
{
	long	elapsed;

	pthread_mutex_lock(&philo[i].meal_mutex);
	elapsed = get_timestamp(data) - philo[i].last_meal_time;
	pthread_mutex_unlock(&philo[i].meal_mutex);
	if (elapsed > data->time_to_die)
	{
		log_action(&philo[i], "died");
		stop_simulation(data);
		return (1);
	}
	return (0);
}

static int	check_all_philosophers_ate(t_philosopher *philo, t_data *data)
{
	int	i;
	int	all_eat_count;

	if (data->meals_required <= 0)
		return (0);
	i = 0;
	all_eat_count = 0;
	while (i < data->philosopher_count)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].meal_count >= data->meals_required)
			all_eat_count++;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	if (all_eat_count == data->philosopher_count)
		return (1);
	return (0);
}

void	*monitor_philosophers(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;
	int				i;

	philo = (t_philosopher *)arg;
	data = philo[0].data;
	while (!is_simulation_stopped(data))
	{
		i = 0;
		while (i < data->philosopher_count)
		{
			if (check_philosopher_death(philo, data, i))
				return (NULL);
			i++;
		}
		if (check_all_philosophers_ate(philo, data))
		{
			stop_simulation(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	create_monitor_thread(pthread_t *monitor_thread, t_data *data,
		t_philosopher *philo)
{
	if (pthread_create(monitor_thread, NULL, monitor_philosophers, philo) != 0)
	{
		printf("Error: failed to create monitor thread\n");
		stop_simulation(data);
		return (1);
	}
	return (0);
}

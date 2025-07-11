/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/11 19:18:55 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(t_data *data)
{
	struct timeval	now;
	long			current_ms;

	gettimeofday(&now, NULL);
	current_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (current_ms - data->start_time);
}

void	log_action(t_philosopher *philo, const char *action)
{
	long	timestamp;

	timestamp = 0;
	timestamp = get_timestamp(philo->data);
	pthread_mutex_lock(&philo->data->log_mutex);
	printf("%03ld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->log_mutex);
}

static void	initialize_philosophers(t_data *data, t_philosopher *philo)
{
	struct timeval	now;
	int				i;

	gettimeofday(&now, NULL);
	data->start_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	i = 0;
	while (i < data->philosopher_count)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		philo[i].last_meal_time = 0;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
}

static int	create_philosopher_threads(t_data *data, t_philosopher *philo,
		int *created_count)
{
	int	i;

	i = 0;
	while (i < data->philosopher_count)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher_routine,
				&philo[i]) != 0)
		{
			printf("Error: failed to create philosopher thread\n");
			stop_simulation(data);
			*created_count = i;
			return (1);
		}
		i++;
	}
	*created_count = i;
	return (0);
}

int	start_simulation(t_data *data, t_philosopher *philo)
{
	int			i;
	int			created_count;
	pthread_t	monitor_thread;

	initialize_philosophers(data, philo);
	if (create_philosopher_threads(data, philo, &created_count))
		return (1);
	if (create_monitor_thread(&monitor_thread, data, philo))
		return (1);
	i = 0;
	while (i < created_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

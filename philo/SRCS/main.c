/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/16 10:29:20 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_resources(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->philosopher_count)
	{
		pthread_mutex_destroy(&philo[i].meal_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->forks);
	free(philo);
	free(data);
}

static int	handle_init_failure(t_data *data, t_philosopher *philo)
{
	if (data)
	{
		free(data->forks);
		free(data);
	}
	if (philo)
		free(philo);
	return (1);
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_philosopher	*philo;

	data = init_data(ac, av);
	if (!data)
		return (1);
	init_start_time(data);
	philo = init_philosophers(data);
	if (!philo)
		return (handle_init_failure(data, NULL));
	if (start_simulation(data, philo) != 0)
		return (handle_init_failure(data, philo));
	cleanup_resources(data, philo);
	return (0);
}

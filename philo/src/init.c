/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/21 15:39:56 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Missing argument\n");
		return (NULL);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philosopher_count = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->meals_required = atoi(av[5]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philosopher_count);
	if (!data->forks)
		return (free(data), NULL);
	while (i < data->philosopher_count)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (data);
}

t_philosopher	*init_philosophers(t_data *data)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	philo = malloc(sizeof(t_philosopher) * data->philosopher_count);
	if (!philo)
		return (NULL);
	// 哲学者の初期化
	while (i < data->philosopher_count)
	{
		philo[i].id = i + 1;
		philo[i].last_meal_time = 0; // 開始時は食事していない
		philo[i].meal_count = 0;
		philo[i].data = data; // 共有データへのポインタを設定
		i++;
	}
	return (philo);
}

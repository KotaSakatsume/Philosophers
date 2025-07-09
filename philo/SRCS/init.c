/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/06 12:20:17 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// プログラム開始時に一度だけ
void	init_start_time(t_data *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	data->start_time = now.tv_sec * 1000 + now.tv_usec / 1000;
}

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
	pthread_mutex_init(&data->stop_mutex, NULL);
	data->stop_flag = 0;
	data->start_time = 0;
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
		philo[i].last_meal_time = data->start_time;
		philo[i].meal_count = 0;
		philo[i].data = data; // 共有データへのポインタを設定
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		i++;
	}
	return (philo);
}

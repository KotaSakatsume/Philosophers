/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/22 11:42:36 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data *data)
{
	printf("philosopher_count: %d\n", data->philosopher_count);
	printf("  time_to_die: %ld\n", data->time_to_die);
	printf("  time_to_eat: %ld\n", data->time_to_eat);
	printf("  time_to_sleep: %ld\n", data->time_to_sleep);
	printf("  meals_required: %d\n", data->meals_required);
	printf("  stop_flag: %d\n", data->stop_flag);
	for (int i = 0; i < data->philosopher_count; i++)
	{
		printf("  Fork %d: %p\n", i, (void *)&data->forks[i]);
	}
}

void	print_philosopher(t_philosopher *philo, int count)
{
	printf("\n");
	for (int i = 0; i < count; i++)
	{
		printf("\n");
		printf("Philosopher %d:\n", philo[i].id);
		printf("|--Last Meal Time: %ld\n", philo[i].last_meal_time);
		printf("|--Meal Count: %d\n", philo[i].meal_count);
		printf("|--Data Pointer: %p\n", (void *)philo[i].data);
		printf("|------------------\n");
	}
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_philosopher	*philo;
	int				i;

	i = 0;
	data = init_data(ac, av);
	if (!data)
		return (1);
	philo = init_philosophers(data);
	if (!philo)
	{
		free(data->forks);
		free(data);
		return (1);
	}
	print_data(data);
	print_philosopher(philo, data->philosopher_count);
	// シミュレーションを実行する（未実装部分）
	// start_simulation(data, philo);
	// リソース解放
	while (i < data->philosopher_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->log_mutex);
	free(data->forks);
	free(philo);
	free(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/02 19:41:36 by kosakats         ###   ########.fr       */
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
	printf("%ld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->log_mutex);
}

int	is_simulation_stopped(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->stop_mutex);
	flag = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (flag);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	*monitor_philosophers(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;
	int				i;
	long			elapsed;
	int				all_eat_count;

	philo = (t_philosopher *)arg;
	data = philo[0].data;
	while (!is_simulation_stopped(data))
	{
		i = 0;
		all_eat_count = 0;
		while (i < data->philosopher_count)
		{
			elapsed = get_timestamp(data) - philo[i].last_meal_time;
			if (elapsed > data->time_to_die)
			{
				log_action(&philo[i], "died");
				stop_simulation(data);
				return (NULL);
			}
			if (data->meals_required > 0
				&& philo[i].meal_count >= data->meals_required)
				all_eat_count++;
			i++;
		}
		if (data->meals_required > 0
			&& all_eat_count == data->philosopher_count)
		{
			stop_simulation(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	take_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philosopher_count;
	// 左のフォークを取る
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	log_action(philo, "has taken a fork");
	// 右のフォークを取る
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	log_action(philo, "has taken a fork");
}

void	eat(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philosopher_count;
	log_action(philo, "is eating");
	philo->last_meal_time = get_timestamp(philo->data);
	philo->meal_count++;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void	ft_sleep(t_philosopher *philo)
{
	log_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philosopher *philo)
{
	log_action(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!is_simulation_stopped(philo->data))
	{
		take_forks(philo);
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	start_simulation(t_data *data, t_philosopher *philo)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->philosopher_count)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher_routine,
				&philo[i]) != 0)
		{
			printf("Error creating thread\n");
			stop_simulation(data);
		}
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_philosophers, philo);
	i = 0;
	while (i < data->philosopher_count)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
}

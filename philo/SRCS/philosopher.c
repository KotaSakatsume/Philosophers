/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/09 13:36:23 by kosakats         ###   ########.fr       */
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
			pthread_mutex_lock(&philo[i].meal_mutex);
			elapsed = get_timestamp(data) - philo[i].last_meal_time;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			if (elapsed > data->time_to_die)
			{
				log_action(&philo[i], "died");
				stop_simulation(data);
				return (NULL);
			}
			if (data->meals_required > 0)
			{
				pthread_mutex_lock(&philo[i].meal_mutex);
				if (philo[i].meal_count >= data->meals_required)
					all_eat_count++;
				pthread_mutex_unlock(&philo[i].meal_mutex);
			}
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
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->data->philosopher_count;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		if (is_simulation_stopped(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[right]);
			return ;
		}
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left]);
		if (is_simulation_stopped(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[left]);
			pthread_mutex_unlock(&philo->data->forks[right]);
			return ;
		}
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		if (is_simulation_stopped(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[left]);
			return ;
		}
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right]);
		if (is_simulation_stopped(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[right]);
			pthread_mutex_unlock(&philo->data->forks[left]);
			return ;
		}
		log_action(philo, "has taken a fork");
	}
}

void	eat(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	if (is_simulation_stopped(philo->data))
		return ;
	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philosopher_count;
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_timestamp(philo->data);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void	ft_sleep(t_philosopher *philo)
{
	if (is_simulation_stopped(philo->data))
		return ;
	log_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philosopher *philo)
{
	if (is_simulation_stopped(philo->data))
		return ;
	log_action(philo, "is thinking");
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

int	start_simulation(t_data *data, t_philosopher *philo)
{
	int				i;
	int				created_count;
	pthread_t		monitor_thread;
	struct timeval	now;

	i = 0;
	created_count = 0;
	gettimeofday(&now, NULL);
	data->start_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	// last_meal_time を start_time に設定しておく
	while (i < data->philosopher_count)
	{
		// philo[i].last_meal_time = 0;
		pthread_mutex_lock(&philo[i].meal_mutex);
		philo[i].last_meal_time = 0;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	// 哲学者スレッドの生成
	while (created_count < data->philosopher_count)
	{
		if (pthread_create(&philo[created_count].thread, NULL,
				philosopher_routine, &philo[created_count]) != 0)
		{
			printf("Error: failed to create philosopher thread\n");
			stop_simulation(data);
			break ;
		}
		created_count++;
	}
	// モニタスレッドの生成
	if (pthread_create(&monitor_thread, NULL, monitor_philosophers, philo) != 0)
	{
		printf("Error: failed to create monitor thread\n");
		stop_simulation(data);
	}
	// スレッドの終了待機
	i = 0;
	while (i < created_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

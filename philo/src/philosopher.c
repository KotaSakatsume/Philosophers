/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/06/26 11:41:33 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philosophers(void *arg)
{
}

void	log_action(t_philosopher *philo, const char *action)
{
	
}

void	take_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->philosopher_count;
	// 左のフォークを取る
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	log_action(philo, "has taken a fork");
	// 右のフォークを取る
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	log_action(philo, "has taken a fork");
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		take_forks(philo);
	}
	return ;
}

void	start_simulation(t_data *data, t_philosopher *philo)
{
	pthread_create(&philo->thread, NULL, philosopher_routine, NULL);
	pthread_create(&philo->thread, NULL, monitor_philosophers, NULL);
}

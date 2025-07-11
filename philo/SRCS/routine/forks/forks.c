/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/11 18:52:25 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks_even(t_philosopher *philo, int left, int right)
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

static void	take_forks_odd(t_philosopher *philo, int left, int right)
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

void	take_forks(t_philosopher *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->data->philosopher_count;
	if (philo->data->philosopher_count == 1)
	{
		pthread_mutex_lock(&philo->data->forks[0]);
		log_action(philo, "has taken a fork");
		while (!is_simulation_stopped(philo->data))
			usleep(100);
		pthread_mutex_unlock(&philo->data->forks[0]);
		return ;
	}
	if (philo->id % 2 == 0)
		take_forks_even(philo, left, right);
	else
		take_forks_odd(philo, left, right);
}

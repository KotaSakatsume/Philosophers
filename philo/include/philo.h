/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:24:26 by kosakats          #+#    #+#             */
/*   Updated: 2025/07/11 19:16:15 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	int				meal_count;
	struct s_data	*data;
	pthread_mutex_t	meal_mutex;
}					t_philosopher;

typedef struct s_data
{
	int				philosopher_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_required;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	int				stop_flag;
	long			start_time;
}					t_data;

// init.c
t_data				*init_data(int ac, char **av);
t_philosopher		*init_philosophers(t_data *data);
void				init_start_time(t_data *data);

// philosopher.c
int					start_simulation(t_data *data, t_philosopher *philo);
int					is_simulation_stopped(t_data *data);
void				log_action(t_philosopher *philo, const char *action);
long				get_timestamp(t_data *data);
void				stop_simulation(t_data *data);

// monitor.c
int					create_monitor_thread(pthread_t *monitor_thread,
						t_data *data, t_philosopher *philo);

// routine.c
void				*philosopher_routine(void *arg);

// ft_atoi.c
int					safe_atoi(const char *str, t_data *data);

// forks.c
void				take_forks(t_philosopher *philo);

// eat.c
void				eat(t_philosopher *philo);

// sleep.c
void				ft_sleep(t_philosopher *philo);

// think.c
void				think(t_philosopher *philo);

#endif
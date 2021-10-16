/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:42:03 by khafni            #+#    #+#             */
/*   Updated: 2021/10/16 17:41:47 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	init_philos_data_helper(char **argv,
	t_philos_data *philos_data)
{
	philos_data->number_of_philos = ft_atoi(argv[1]);
	philos_data->time_to_die = ft_atoi(argv[2]);
	philos_data->time_to_eat = ft_atoi(argv[3]);
	philos_data->time_to_sleep = ft_atoi(argv[4]);
	philos_data->start_time = actual_time();
	philos_data->is_a_philo_dead = 1;
}

void	philos_init_helper(t_one_philo_data	*philos,
	t_philos_data *philos_data, int i)
{
	pthread_mutex_init(&(philos[i].mutex), NULL);
	pthread_mutex_init(&(philos[i].eating_lock), NULL);
	pthread_mutex_init(&(philos[i].eating_count_lock), NULL);
	philos[i].last_time_ate = actual_time() - philos_data->start_time;
	philos[i].number_of_times_ate = 0;
	philos[i].data = philos_data;
	philos[i].id = i;
}

t_one_philo_data	*init_philos_data(int argc, char **argv)
{
	t_one_philo_data	*philos;
	t_philos_data		*philos_data;
	int					i;
	int					n_of_phs;

	philos_data = malloc(sizeof(struct s_philos_data));
	init_philos_data_helper(argv, philos_data);
	n_of_phs = philos_data->number_of_philos;
	philos = malloc(sizeof(struct s_one_philo_data) * n_of_phs);
	if (argc == 6)
		philos_data->num_times_each_philo_eat = ft_atoi(argv[5]);
	else
		philos_data->num_times_each_philo_eat = -1;
	i = 0;
	while (i < philos_data->number_of_philos)
	{	
		philos_init_helper(philos, philos_data, i);
		i++;
	}
	pthread_mutex_init(&philos_data->death_lock, NULL);
	pthread_mutex_init(&philos_data->last_meal_lock, NULL);
	philos_data->philos = philos;
	return (philos);
}

int	waiter(t_one_philo_data *philos)
{
	int				i;
	t_philos_data	*data;

	data = philos[0].data;
	i = 0;
	while (i < data->number_of_philos)
	{	
		pthread_create(&(philos[i].thread), NULL, philo_routine, &philos[i]);
		usleep(100);
		i++;
	}
	supervisor(philos);
	return (WAITER_TERMINATE);
}

void	print_status(int which_state, t_one_philo_data *philo)
{	
	int				index;
	unsigned long	time;
	t_philos_data	*data;

	data = philo->data;
	time = actual_time() - data->start_time;
	index = philo->id;
	index++;
	pthread_mutex_lock(&data->death_lock);
	time = actual_time() - data->start_time;
	if (which_state == EATING_STATE)
		printf("%lu %d is eating\n", time, index);
	else if (which_state == THINKING_STATE)
		printf("%lu %d is thinking\n", time, index);
	else if (which_state == FORK_GET_STATE)
		printf("%lu %d has taken a fork\n", time, index);
	else if (which_state == DEATH_STATE)
		printf("%lu %d died\n", time, index);
	else if (which_state == SLEEPING_STATE)
		printf("%lu %d is sleeping\n", time, index);
	if (which_state != DEATH_STATE)
		pthread_mutex_unlock(&data->death_lock);
}

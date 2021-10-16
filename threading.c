/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:39:13 by khafni            #+#    #+#             */
/*   Updated: 2021/10/16 17:38:52 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_subroutine(t_one_philo_data *philo)
{
	t_philos_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->mutex);
	print_status(FORK_GET_STATE, philo);
	pthread_mutex_lock(&data->philos[(philo->id + 1)
		% data->number_of_philos].mutex);
	print_status(FORK_GET_STATE, philo);
	pthread_mutex_lock(&data->last_meal_lock);
	philo->last_time_ate = actual_time() - data->start_time;
	pthread_mutex_unlock(&data->last_meal_lock);
	pthread_mutex_lock(&philo->eating_count_lock);
	philo->number_of_times_ate++;
	pthread_mutex_unlock(&philo->eating_count_lock);
	pthread_mutex_lock(&philo->eating_lock);
	print_status(EATING_STATE, philo);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&philo->eating_lock);
	print_status(SLEEPING_STATE, philo);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&data->philos[(philo->id + 1)
		% data->number_of_philos].mutex);
	ft_usleep(data->time_to_sleep);
	print_status(THINKING_STATE, philo);
}

void	*philo_routine(void *philo_)
{
	t_one_philo_data	*philo;
	t_philos_data		*data;

	philo = philo_;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&data->death_lock);
	while (data->is_a_philo_dead && philo->number_of_times_ate
		< (int)data->num_times_each_philo_eat)
	{
		pthread_mutex_unlock(&data->death_lock);
		philo_subroutine(philo);
		pthread_mutex_lock(&data->death_lock);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (NULL);
}

void	supervisor_helper(t_supervisor	*sup)
{
	sup->philo = sup->philos[sup->i];
	pthread_mutex_lock(&sup->data->last_meal_lock);
	sup->last_meal = sup->philo.last_time_ate;
	pthread_mutex_unlock(&sup->data->last_meal_lock);
	sup->timenow = actual_time() - sup->data->start_time;
}

void	supervisor(t_one_philo_data *philos)
{
	t_supervisor	sup;

	sup.philos = philos;
	sup.data = philos[0].data;
	while (1)
	{	
		sup.i = 0;
		while (sup.i < sup.data->number_of_philos)
		{	
			supervisor_helper(&sup);
			if (sup.timenow - sup.philo.last_time_ate > sup.data->time_to_die)
			{
				pthread_mutex_lock(&sup.philo.eating_lock);
				pthread_mutex_lock(&sup.data->death_lock);
				sup.data->is_a_philo_dead = 0;
				pthread_mutex_unlock(&sup.data->death_lock);
				print_status(DEATH_STATE, &sup.philo);
				return ;
			}
			pthread_mutex_unlock(&sup.philo.eating_lock);
			sup.i++;
		}
	}
}

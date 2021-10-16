/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:16:07 by khafni            #+#    #+#             */
/*   Updated: 2021/10/16 17:19:22 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include "tools.h"
# include <pthread.h>
# include <sys/time.h>
# define WAITER_TERMINATE -666
# define THINKING_STATE 0
# define EATING_STATE 1
# define HUNGRY_STATE 2
# define DEATH_STATE 3
# define FORK_GET_STATE 4
# define SLEEPING_STATE 5

typedef struct s_one_philo_data
{
	pthread_mutex_t			mutex;
	unsigned long int		last_time_ate;
	pthread_t				thread;
	pthread_t				suprv_thread;
	int						number_of_times_ate;
	int						id;
	pthread_mutex_t			eating_lock;
	pthread_mutex_t			eating_count_lock;
	void					*data;
}	t_one_philo_data;

typedef struct s_philos_data
{
	int					number_of_philos;
	unsigned long		start_time;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		num_times_each_philo_eat;	
	int					is_a_philo_dead;		
	pthread_mutex_t		writelock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		last_meal_lock;	
	t_one_philo_data	*philos;
}	t_philos_data;

typedef struct s_philos_data_w
{
	int				which_philo;
	int				is_a_philo_dead;
	t_philos_data	*data;	
}	t_philos_data_w;

typedef struct s_supervisor
{
	unsigned long int	timenow;
	unsigned long		last_meal;
	int					i;
	t_one_philo_data	*philos;
	t_one_philo_data	philo;
	t_philos_data		*data;
}	t_supervisor;

void					ft_usleep(long int time_in_ms);
int						parse_args(int argc, char **argv);
int						checkIfNonNumeric(char *argument);
int						checkIfNegative(char *argument);
void					print_status(int which_state, t_one_philo_data *philo);
t_philos_data			*get_philos_data(void);
t_one_philo_data		*init_philos_data(int argc, char **argv);
int						waiter(t_one_philo_data *philos);
unsigned long int		actual_time(void);
void					*philo_routine(void *philo_);
void					philo_subroutine(t_one_philo_data *philo);
void					supervisor(t_one_philo_data *philo);
#endif
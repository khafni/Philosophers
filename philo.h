#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include "tools.h"
# include <pthread.h>
# include <sys/time.h>
# define WAITER_TERMINATE -666

typedef struct s_one_philo_data
{
	pthread_mutex_t	mutex;
	long int		last_time_ate;
	pthread_t		thread;
} t_one_philo_data;

typedef struct s_philos_data
{
	int number_of_philosopher;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;	
	int	is_a_philo_dead;
	t_one_philo_data	*philos;
} t_philos_data;

typedef struct s_philos_data_w
{
	int which_philo;
	t_philos_data *data;	
} t_philos_data_w;


t_philos_data	*get_philos_data(void);
t_philos_data	*init_philos_data(int argc, char **argv);
int				waiter(void *data_);
void			*philo_routine(void *data_);
#endif
#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include "tools.h"
# include <pthread.h>

typedef struct s_philos_data
{
	int number_of_philosopher;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t *mutexes;
} t_philos_data;

t_philos_data *get_philos_data(void);
void init_philos_data(int argc, char **argv);
void spawn_philosophers(void);
#endif
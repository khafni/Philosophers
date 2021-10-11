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
	pthread_mutex_t	mutex;
	unsigned long int		last_time_ate;
	pthread_t		thread;
	pthread_t		suprv_thread;
} t_one_philo_data;

typedef struct s_philos_data
{
	int number_of_philosopher;
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	int number_of_times_each_philosopher_must_eat;	
	int	is_a_philo_dead;
	t_one_philo_data	*philos;	
	int					*philos_states;
	pthread_mutex_t		philos_states_lock;
} t_philos_data;

typedef struct s_philos_data_w
{
	int which_philo;
	int is_a_philo_dead;
	t_philos_data *data;	
} t_philos_data_w;



void print_status(int n, int which_state, unsigned long int time);

t_philos_data	*get_philos_data(void);
t_philos_data	*init_philos_data(int argc, char **argv);
int				waiter(void *data_);

void			*philo_routine(void *data_);
void			*superv_routine(void *data_);
#endif
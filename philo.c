#include "philo.h"

long int		actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;	
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}


t_philos_data *get_philos_data(void)
{
	static t_philos_data *phs_data = NULL;

	if (phs_data == NULL)
	{
		phs_data = malloc(sizeof(struct s_philos_data));
		phs_data->number_of_philosopher = 0;
		phs_data->number_of_times_each_philosopher_must_eat = 0;
		phs_data->time_to_die = 0;
		phs_data->time_to_eat = 0;
		phs_data->time_to_sleep = 0;
	}
	return (phs_data);
}

t_philos_data	*init_philos_data(int argc, char **argv)
{
	t_philos_data *philos_data;
	int i;
	
	if (argc < 5 || argc > 6)
		return (NULL);
	 //philos_data = get_philos_data();
	philos_data = malloc(sizeof(t_philos_data));
	philos_data->philos = malloc(sizeof(t_one_philo_data) * philos_data->number_of_philosopher);
	philos_data->number_of_philosopher = ft_atoi(argv[1]);
	philos_data->time_to_die = ft_atoi(argv[2]);
	philos_data->time_to_eat = ft_atoi(argv[3]);
	philos_data->time_to_sleep = ft_atoi(argv[4]);
 	if (argc == 6)
		philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);	
	else
		philos_data->number_of_times_each_philosopher_must_eat = -1;
	philos_data->mutexes = malloc(philos_data->number_of_philosopher * sizeof(pthread_mutex_t));
	i = 0;
	while (i < philos_data->number_of_philosopher)
	{
		philos_data->philos[i].last_time_ate = actual_time();
		pthread_mutex_init(&(philos_data->philos[i].mutex), NULL);
		i++;
	}
	return (philos_data);
}

void	pthread_create_helper(pthread_t *thread_addr, thread_routine)

void waiter(void *data_)
{
	t_philos_data	*data;
	int				i;

	data = data_;
	i = 0;
	while (i < data->number_of_philosopher)
	{
		pthread_create(&(data->philos[i].thread), NULL, philo_routine, data_);
		i++;
	}	
}

void philo_routine(void *data_)
{
	t_philos_data *data;

	data = data_;
	pthread_mutex_lock(data->mutexes);
	
	pthread_mutex_unlock(data);
}

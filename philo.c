#include "philo.h"

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

void init_philos_data(int argc, char **argv)
{
	t_philos_data *philos_data;
	int i;
	
	philos_data = get_philos_data();
	philos_data->number_of_philosopher = ft_atoi(argv[1]);
	philos_data->time_to_die = ft_atoi(argv[2]);
	philos_data->time_to_eat = ft_atoi(argv[3]);
	philos_data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[4]);	
	else
		philos_data->number_of_times_each_philosopher_must_eat = -1;
	philos_data->mutexes = malloc(philos_data->number_of_philosopher * sizeof(pthread_mutex_t));
	i = 0;
	while (i < philos_data->number_of_philosopher)
	{
		pthread_mutex_init(philos_data->mutexes + i, NULL);
		i++;
	}
}

/* void spawn_philosophers(void)
{
	
}
 */
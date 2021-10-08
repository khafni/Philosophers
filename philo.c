#include "philo.h"


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

unsigned long int		actual_time(void)
{
	unsigned long int			time;
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	time = 0;	
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

t_philos_data	*init_philos_data(int argc, char **argv)
{
	t_philos_data *philos_data;
	int i;
	
	if (argc < 5 || argc > 6)
		return (NULL);
	philos_data = malloc(sizeof(struct s_philos_data));
	philos_data->number_of_philosopher = ft_atoi(argv[1]);
	philos_data->time_to_die = ft_atoi(argv[2]);
	philos_data->time_to_eat = ft_atoi(argv[3]);
	philos_data->time_to_sleep = ft_atoi(argv[4]);
	philos_data->is_a_philo_dead = 0;
	philos_data->philos = malloc(sizeof(struct s_one_philo_data) * philos_data->number_of_philosopher);	
 	if (argc == 6)
		philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);	
	else
		philos_data->number_of_times_each_philosopher_must_eat = -1;	
	i = 0;
	while (i < philos_data->number_of_philosopher)
	{
		philos_data->philos[i].last_time_ate = actual_time();
		pthread_mutex_init(&(philos_data->philos[i].mutex), NULL);
		i++;
	}
	return (philos_data);
}

/* void	pthread_create_helper(pthread_t *thread_addr,
	void *(*routine)(void *data),
	void *arg, int which_philo)
{
	pthreasd
} */

void launch_threads(void *data_)
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

int	waiter(void *data_)
{
	t_philos_data	*data;	
	int				i;
	t_philos_data_w	d_w_indx;// = malloc(sizeof(t_philos_data_w));

	data = data_;
	d_w_indx.data = data;	
	i = 0;

	while (i < data->number_of_philosopher)
	{
		d_w_indx.which_philo = i;
		// printf(":) %d\n", d_w_indx.which_philo);
		pthread_create(&(data->philos[i].thread), NULL, philo_routine, &d_w_indx);
		usleep(100);
		i++;
	}
	

	i = 0;
	while (i < data->number_of_philosopher)
	{
		d_w_indx.which_philo = i;
		pthread_join(data->philos[i].thread, NULL);	
		i++;
	}

	// while (1)
	// {
	// 	if (data->is_a_philo_dead == 1)
	// 	{
		
	// 		break ;
	// 	}
	// }
	// free(data->philos);
	// free(data);
	// i = 0;
	// while (i < data->number_of_philosopher)
	// {
	// 	pthread_mutex_destroy(&(data->philos[i].mutex));
	// 	i++;
	// }
	return (WAITER_TERMINATE);	
}

void *philo_routine(void *data_)
{
	t_philos_data_w *data_w;
	int				index;

	
	data_w = data_;
	// pthread_mutex_lock(&lock);
	index = data_w->which_philo;	
	//printf("the magic index %d\n", index);
	// pthread_mutex_unlock(&lock);
	while (1)
	{
		if (data_w->data->is_a_philo_dead)
		{
			return (NULL);
		}
		printf("%ld %ld %ld %ld\n", actual_time(), data_w->data->philos[index].last_time_ate, data_w->data->time_to_die,
		actual_time() - data_w->data->philos[index].last_time_ate);

		if (actual_time() - data_w->data->philos[index].last_time_ate >= data_w->data->time_to_die)
		{	
			printf("philo : %d died\n", index);
			data_w->data->is_a_philo_dead = 1;	
			return (NULL);
		} 
		// if (index)
			// printf("%d\n", index);
		pthread_mutex_lock(&(data_w->data->philos[index % 5].mutex));
		pthread_mutex_lock(&(data_w->data->philos[(index + 1) % 5].mutex));
		//printf("%ld %d %s\n", actual_time(), index, "has taken a fork");
		pthread_mutex_unlock(&(data_w->data->philos[index].mutex));
		pthread_mutex_unlock(&(data_w->data->philos[(index + 1) % 5].mutex));
	}
	//pthread_mutex_unlock(&lock);
	return (NULL);
}

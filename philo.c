#include "philo.h"

unsigned long int		actual_time(void)
{
	unsigned long int			time;
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	time = 0;	
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;



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
	philos_data->is_a_philo_dead = 1;
	philos_data->philos = malloc(sizeof(struct s_one_philo_data) * philos_data->number_of_philosopher);	
	philos_data->philos_states = malloc(sizeof(int) * philos_data->number_of_philosopher);	
 	if (argc == 6)
		philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);	
	else
		philos_data->number_of_times_each_philosopher_must_eat = -1;	
	i = 0;
	while (i < philos_data->number_of_philosopher)
	{
		philos_data->philos[i].last_time_ate = actual_time();
		pthread_mutex_init(&(philos_data->philos[i].mutex), NULL);
		philos_data->philos_states[i] = THINKING_STATE;
		philos_data->philos[i].last_time_ate = actual_time();
		i++;
	}
	pthread_mutex_init(&philos_data->philos_states_lock, NULL);
	return (philos_data);
}

/* void	pthread_create_helper(pthread_t *thread_addr,
	void *(*routine)(void *data),
	void *arg, int which_philo)
{
	pthreasd
} */

int	waiter(void *data_)
{
	t_philos_data	*data;	
	int				i;
	t_philos_data_w	d_w_indx;// = malloc(sizeof(t_philos_data_w));
	unsigned long int timenow = 0;

	// printf("HELLO");
	data = data_;
	d_w_indx.data = data;	
	i = 0;
	d_w_indx.data->start_time = actual_time();
	while (i < data->number_of_philosopher)
	{
		d_w_indx.which_philo = i;
		// printf(":) %d\n", d_w_indx.which_philo);
		pthread_create(&(data->philos[i].thread), NULL, philo_routine, &d_w_indx);
		pthread_create(&(data->philos[i].suprv_thread), NULL, superv_routine, &d_w_indx);
		ft_usleep(100);
		i++;
	}
	

	// i = 0;
	// while (i < data->number_of_philosopher)
	// {
	// 	d_w_indx.which_philo = i;
	// 	pthread_join(data->philos[i].thread, NULL);	
	// 	i++;
	// }
		
	while (data->is_a_philo_dead)
	{	
		// i = 0;
		// timenow = actual_time();
		// while (i < data->number_of_philosopher)
		// {	
		// 	pthread_mutex_lock(&data->philos_states_lock);
		// 	if (timenow - data->philos[i].last_time_ate >= data->time_to_die)
		// 	{
		// 		print_status(i, DEATH_STATE, (timenow));
		// 		data->is_a_philo_dead = 0;
		// 	}
		// 	pthread_mutex_lock(&data->philos_states_lock);
		// 	i++;
			continue ;
		
			// i = 0;
			// while (i < data->number_of_philosopher)
			// {
				
			// 	i++;
			// }
		
		
	}
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

void print_status(int index, int which_state, unsigned long int time)
{
	pthread_mutex_lock(&lock);
	if (which_state == EATING_STATE)
		printf("%ld %d is eating\n", time, index);	
	else if (which_state == THINKING_STATE)	
		printf("%ld %d is thinking\n", time, index);
	else if (which_state == FORK_GET_STATE)
		printf("%ld %d has taken a fork\n", time, index);
	else if (which_state == DEATH_STATE)
		printf("%ld %d died\n", time, index);
	else if (which_state == SLEEPING_STATE)
		printf("%ld %d is sleeping\n", time, index);	
	if (which_state != DEATH_STATE)	
		pthread_mutex_unlock(&lock);
	// ft_usleep(100);
}

void			*superv_routine(void *data_)
{
	// printf("dnc\n");
	t_philos_data_w *data_w;
	unsigned long int timenow = 0;
	int	index;

	data_w = data_;
	// printf("frw\n");
	index = data_w->which_philo;
	while (data_w->data->is_a_philo_dead)
	{
	
		// pthread_mutex_lock(&data_w->data->philos_states_lock);
		// printf("donc\n");
		//exit(0);	
		// timenow = actual_time() - data_w->data->start_time;
		// printf("wesh : %ld\n", data_w->data->philos[index].last_time_ate);
		timenow = actual_time();
		if (data_w->data->philos_states[index] == EATING_STATE)
		{
			// printf("obbo %d\n", data_w->data->philos_states[index]);
			continue ;
		}
		if (timenow - data_w->data->philos[index].last_time_ate >= data_w->data->time_to_die)
		{	
			print_status(index, DEATH_STATE, (timenow - data_w->data->start_time));
			data_w->data->is_a_philo_dead = 0;
		}
		// pthread_mutex_unlock(&data_w->data->philos_states_lock);
	}
	return (0);
}

void *philo_routine(void *data_)
{
	t_philos_data_w *data_w;
	int				index;

	
	data_w = data_;
	// pthread_mutex_lock(&lock);
	index = data_w->which_philo;
	// if (index == 1)
		// exit(0);
	// if (index % 2 == 0)
		// ft_usleep(100);
	//printf("the magic index %d\n", index);
	// pthread_mutex_unlock(&lock);
	
	// data_w->data->philos[index].last_time_ate = actual_time();
	// printf("%d\n", index);
	while (data_w->data->is_a_philo_dead)
	{

		
		pthread_mutex_lock(&(data_w->data->philos[(index + (index % 2))  % data_w->data->number_of_philosopher].mutex));
		print_status(index, FORK_GET_STATE, actual_time() - data_w->data->start_time);
		// if (data_w->data->number_of_philosopher != 1)	
		// {
		pthread_mutex_lock(&(data_w->data->philos[(index + ((index + 1) % 2)) % data_w->data->number_of_philosopher].mutex));	
		print_status(index, FORK_GET_STATE, actual_time()- data_w->data->start_time);
		// }
		print_status(index, EATING_STATE, actual_time() - data_w->data->start_time);
		data_w->data->philos_states[index] = EATING_STATE;
		// 	printf("philo : %d died\n", index);
		ft_usleep(data_w->data->time_to_eat);
		data_w->data->philos[index].last_time_ate = actual_time();
		print_status(index, SLEEPING_STATE, actual_time() - data_w->data->start_time);
		data_w->data->philos_states[index] = SLEEPING_STATE;
		ft_usleep(data_w->data->time_to_sleep);
		//printf("%ld %d %s\n", actual_time(), index, "has taken a fork");
		pthread_mutex_unlock(&(data_w->data->philos[(index + (index % 2))  % data_w->data->number_of_philosopher].mutex));
		// if (data_w->data->number_of_philosopher != 1)
		pthread_mutex_unlock(&(data_w->data->philos[(index + ((index + 1) % 2)) % data_w->data->number_of_philosopher].mutex));
		print_status(index, THINKING_STATE, actual_time() - data_w->data->start_time);
		data_w->data->philos_states[index] = THINKING_STATE;
	 }
	//pthread_mutex_unlock(&lock);
	return (NULL);
}

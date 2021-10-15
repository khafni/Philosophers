#include "philo.h"
#include <pthread.h>


int check_number_of_times_ate(void *data_)
{
	t_philos_data	*data;
	int				i;

	data = data_;
	i = 0;
	while (i < data->number_of_philosopher)
	{
		if (data->philos[i].number_of_times_ate < data->number_of_times_each_philosopher_must_eat)
			return (0);
		i++;
	}
	return (1);
}

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
	while ((long)(actual_time() - start_time) < time_in_ms)
		usleep((time_in_ms) / 10);
}




t_philos_data	*init_philos_data(int argc, char **argv)
{
	t_one_philo_data *philos;
	t_philos_data *philos_data;
	int i;
	
	if (argc < 5 || argc > 6)
		return (NULL);
	philos_data = malloc(sizeof(struct s_philos_data));
	philos_data->number_of_philosopher = ft_atoi(argv[1]);
	philos_data->time_to_die = ft_atoi(argv[2]);
	philos_data->time_to_eat = ft_atoi(argv[3]);
	philos_data->time_to_sleep = ft_atoi(argv[4]);
	philos_data->start_timem = actual_time();
	philos_data->is_a_philo_dead = 1;
	philos = malloc(sizeof(struct s_one_philo_data) * philos_data->number_of_philosopher);	
	// philos_data->philos_states = malloc(sizeof(int) * (philos_data->number_of_philosopher + 1));	
 	if (argc == 6)
		philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);	
	else
		philos_data->number_of_times_each_philosopher_must_eat = -1;	
	i = 0;
	while (i < philos_data->number_of_philosopher)
	{	
		pthread_mutex_init(&(philos[i].mutex), NULL);	
		philos[i].last_time_ate = actual_time();
		philos[i].number_of_times_ate = 0;
		philos[i].data = philos_data;
		philos[i].id = i;	
		i++;
	}
	pthread_mutex_init(&philos_data->philos_states_lock, NULL);
	pthread_mutex_init(&philos_data->death_lock, NULL);
	pthread_mutex_init(&philos_data->last_meal_lock, NULL);
	// pthread_mutex_init(&philos_data->philos_states_lock, NULL);
	philos_data->philos = philos;
	return (philos_data);
}

int	waiter(t_one_philo_data *philos)
{
	int				i;
	
	i = 0;
	while (i < data->number_of_philosopher)
	{	
		pthread_create(&(philos[i].thread), NULL, philo_routine, philos[i]);	
		usleep(100);
		i++;
	}	
	return (WAITER_TERMINATE);	
}

void print_status(int which_state, t_one_philo_data *philo)
{
	//index++;
	unsigned long	time;
	time = actual_time() - philo->start_time;
	// time =  data->start_time;
	pthread_mutex_lock(&philo->data->death_lock);
	//time = actual_time() - data_w->data->start_time;
	if (which_state == EATING_STATE)
		printf("%lu %d is eating\n", time, philo->id);	
	else if (which_state == THINKING_STATE)	
		printf("%lu %d is thinking\n", time, philo->id);
	else if (which_state == FORK_GET_STATE)
		printf("%lu %d has taken a fork\n", time, philo->id);
	else if (which_state == DEATH_STATE)
		printf("%lu %d died %d\n", time, philo->id);
	else if (which_state == SLEEPING_STATE)
		printf("%lu %d is sleeping %d\n", time, philo->id);		
	pthread_mutex_unlock(&philo->data->death_lock);
	// ft_usleep(5);
}

void			*superv_routine(t_one_philo_data *philo)
{	

	unsigned long int timenow;

	while (data_w->data->is_a_philo_dead)
	{
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
			data_w->data->is_a_philo_dead = 0;
			data_w->data->philos_states[index] = DEATH_STATE;
			pthread_mutex_lock(&data_w->data->philos_states_lock);
			print_status(index, DEATH_STATE, (timenow - data_w->data->start_time), data_w);
			// return (NULL);
			// pthread_mutex_unlock(&data_w->data->philos_states_lock);
			// printf("HELLO");
			pthread_mutex_unlock(&data_w->data->philos_states_lock);
			return (NULL);
		}
		// usleep(50);
	}
	return (0);
}
void			philo_subroutine(t_one_philo_data *philo)
{
	pthread_mutex_lock(&philo->mutex);
	print_status(FORK_GET_STATE, philo);
	pthread_mutex_lock(&philo->data->philos[(i + 1) % philo->data->number_of_philosopher].mutex);
	print_status(FORK_GET_STATE, philo);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_time_ate = actual_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->last_meal_lock);
	print_status(EATING_STATE, philo);
	ft_usleep(philo->data->time_to_eat);
	print_status(SLEEPING_STATE, philo);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->data->philos[(i + 1) % philo->data->number_of_philosopher].mutex);
	ft_usleep(philo->data->time_to_sleep);
	print_status(THINKING_STATE, philo);
}

void *philo_routine(t_one_philo_data *philo)
{
	if (philos->id % 2 == 0)
		usleep(100);	
	pthread_mutex_lock(&philo->data->death_lock);
	while (philo->data->is_a_philo_dead)
	{
		pthread_mutex_unlock(&philo->data->death_lock);	
		philo_subroutine(philo);
		pthread_mutex_lock(&philo->data->death_lock);	
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (NULL);
}

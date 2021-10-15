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

t_one_philo_data	*init_philos_data(int argc, char **argv)
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
	philos_data->start_time = actual_time();
	philos_data->is_a_philo_dead = 1;
	philos = malloc(sizeof(struct s_one_philo_data) * philos_data->number_of_philosopher);	
 	if (argc == 6)
		philos_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);	
	else
		philos_data->number_of_times_each_philosopher_must_eat = -1;	
	i = 0;
	while (i < philos_data->number_of_philosopher)
	{	
		pthread_mutex_init(&(philos[i].mutex), NULL);
		pthread_mutex_init(&(philos[i].eating_lock), NULL);
		pthread_mutex_init(&(philos[i].eating_count_lock), NULL);
		philos[i].last_time_ate = actual_time() - philos_data->start_time;
		philos[i].number_of_times_ate = 0;
		philos[i].data = philos_data;
		philos[i].id = i;	
		i++;
	}
	pthread_mutex_init(&philos_data->death_lock, NULL);
	pthread_mutex_init(&philos_data->last_meal_lock, NULL);	
	philos_data->philos = philos;
	return (philos);
}

int	waiter(t_one_philo_data *philos)
{
	int				i;
	t_philos_data	*data;
	
	data = philos[0].data;
	i = 0;
	while (i < data->number_of_philosopher)
	{	
		pthread_create(&(philos[i].thread), NULL, philo_routine, &philos[i]);	
		usleep(100);
		i++;
	}
	supervisor(philos);
	// i = 0;
	// while (i < data->number_of_philosopher)
	// {	
	// 	pthread_join(philos[i].thread, NULL);		
	// 	i++;
	// }
	return (WAITER_TERMINATE);	
}

void print_status(int which_state, t_one_philo_data *philo)
{
	//index++;
	int				index;
	unsigned long	time;
	t_philos_data	*data;

	data = philo->data;
	time = actual_time() - data->start_time;
	index = philo->id;
	index++;
	// time =  data->start_time;
	pthread_mutex_lock(&data->death_lock);
	time = actual_time() - data->start_time;
	if (which_state == EATING_STATE)
		printf("%lu %d is eating\n", time, index);	
	else if (which_state == THINKING_STATE)	
		printf("%lu %d is thinking\n", time, index);
	else if (which_state == FORK_GET_STATE)
		printf("%lu %d has taken a fork\n", time, index);
	else if (which_state == DEATH_STATE)
		printf("%lu %d died\n", time, index);
	else if (which_state == SLEEPING_STATE)
		printf("%lu %d is sleeping\n", time, index);
	if (which_state != DEATH_STATE)
		pthread_mutex_unlock(&data->death_lock);
	// ft_usleep(5);
}



void			supervisor(t_one_philo_data *philos)
{	
	unsigned long int timenow;
	unsigned long		last_meal;

	int					i;
	t_one_philo_data	philo;
	t_philos_data	*data;


	data = philos[0].data;
	while (1)
	{	
		i = 0;
		while (i < data->number_of_philosopher)	
		{
			philo = philos[i];
			pthread_mutex_lock(&data->last_meal_lock);
			last_meal = philo.last_time_ate;
			pthread_mutex_unlock(&data->last_meal_lock);
			timenow = actual_time() - data->start_time;
			
			if (timenow - philo.last_time_ate > data->time_to_die)
			{
				pthread_mutex_lock(&philo.eating_lock); //eating lock
				pthread_mutex_lock(&data->death_lock);
				data->is_a_philo_dead = 0;
				pthread_mutex_unlock(&data->death_lock);	
				print_status(DEATH_STATE, &philo);
				return ;
			}
			pthread_mutex_unlock(&philo.eating_lock); //eating unlock
			i++;
		}
	}
}

void			philo_subroutine(t_one_philo_data *philo)
{
	t_philos_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->mutex);
	print_status(FORK_GET_STATE, philo);
	pthread_mutex_lock(&data->philos[(philo->id + 1) % data->number_of_philosopher].mutex);
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
	pthread_mutex_unlock(&data->philos[(philo->id + 1) % data->number_of_philosopher].mutex);
	ft_usleep(data->time_to_sleep);
	print_status(THINKING_STATE, philo);
}

void *philo_routine(void *philo_)
{
	t_one_philo_data *philo;
	t_philos_data *data;

	philo = philo_;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(100);	
	pthread_mutex_lock(&data->death_lock);
	while (data->is_a_philo_dead && philo->number_of_times_ate < data->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(&data->death_lock);	
		philo_subroutine(philo);
		pthread_mutex_lock(&data->death_lock);	
	}
	pthread_mutex_unlock(&data->death_lock);
	return (NULL);
}

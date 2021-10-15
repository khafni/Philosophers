#include "philo.h"
#include <pthread.h>
#include <string.h>

int main(int argc, char **argv)
{
	t_one_philo_data *data;

	data = init_philos_data(argc, argv);
	if (!data)
	{
		printf("error\n");
		return (1);
	}
	waiter(data);
	// while (waiter(data) != WAITER_TERMINATE)
	// {
		// continue ;
	// }	
	// char *str = strdup("fuckgyigilgyilgliygyligligyilgyilgyigjk");
	// free(str);

	// int i = 0;
	// pthread_mutex_destroy(&data->philos_states_lock);
	// while (i < data->number_of_philosopher)
	// {
	// 	pthread_mutex_destroy(&data->philos[i].mutex);
	// 	pthread_detach(data->philos[i].thread);
	// 	pthread_detach(data->philos[i].suprv_thread);
	// 	i++;
	// }
	// free(data->philos);
	// free(data);
	// write(1,"11111\n",6);
	// while (1)
		// ;
	// system("leaks philo");
	return (0);
}
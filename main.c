#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

int main(int argc, char **argv)
{	
	if (argc < 5 || argc > 6)
	{
		write(2, "wrong arguments for the program\n", 32);
		return (1);
	}
	
	init_philos_data(argc, argv);
	t_philos_data *data = get_philos_data();
		
	printf("number of philosophers : %d", data->number_of_philosopher);
	return (0);
}
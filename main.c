#include "philo.h"

int main(int argc, char **argv)
{
	t_philos_data *data;

	data = init_philos_data(argc, argv);
	if (!data)
		return (1);
	printf("%d", data->number_of_times_each_philosopher_must_eat);
	return (0);
}
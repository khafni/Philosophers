#include "philo.h"
#include <string.h>

int main(int argc, char **argv)
{
	t_philos_data *data;

	data = init_philos_data(argc, argv);
	if (!data)
	{
		printf("error\n");
		return (1);
	}
	if (waiter(data) == WAITER_TERMINATE)
	{
		printf("DEATH\n");
		return (666);
	}	
	// free(data->philos);
	// free(data);
	// char *str = strdup("fuckgyigilgyilgliygyligligyilgyilgyigjk");
	// free(str);
	return (0);
}
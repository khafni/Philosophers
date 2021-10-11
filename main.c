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
	while (waiter(data) != WAITER_TERMINATE)
	{
		continue ;
	}	
	// free(data->philos);
	// free(data);
	// char *str = strdup("fuckgyigilgyilgliygyligligyilgyilgyigjk");
	// free(str);
	return (0);
}
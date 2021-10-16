/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:33:07 by khafni            #+#    #+#             */
/*   Updated: 2021/10/16 15:33:07 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_one_philo_data	*data;

	if (!parse_args(argc, argv))
		return (1);
	data = init_philos_data(argc, argv);
	if (!data)
	{
		printf("error\n");
		return (1);
	}
	waiter(data);
	return (0);
}

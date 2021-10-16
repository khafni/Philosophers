/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:37:19 by khafni            #+#    #+#             */
/*   Updated: 2021/10/16 19:00:44 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	actual_time(void)
{
	unsigned long int			time;
	struct timeval				current_time;

	gettimeofday(&current_time, NULL);
	time = 0;
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(unsigned long time_in_ms)
{
	unsigned long	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep((time_in_ms) / 10);
}

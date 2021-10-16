/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:32:23 by khafni            #+#    #+#             */
/*   Updated: 2021/10/16 17:44:33 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	checkIfNonNumeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("wrong argument\n");
		return (0);
	}
	if (ft_atoi(argv[1]) == 0)
	{
		printf("0 philosophers???? what are you trying to do????\n");
		return (0);
	}
	while (i < argc)
	{
		if (!checkIfNonNumeric(argv[i]))
		{
			printf("wrong argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}

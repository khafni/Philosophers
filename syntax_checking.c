/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:32:23 by khafni            #+#    #+#             */
/*   Updated: 2021/10/16 19:18:26 by khafni           ###   ########.fr       */
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

int	check_if_arg_is_big(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
			j++;
		if (j > 10)
		{
			printf("arg with an illogically huge number ");
			printf("you don't want your philosopher to sleep for eternity ");
			printf("or something :/\n");
			return (1);
		}
		i++;
	}
	return (0);
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
	if (check_if_arg_is_big(argc, argv))
		return (0);
	return (1);
}

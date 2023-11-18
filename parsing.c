/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:34:37 by ndesprez          #+#    #+#             */
/*   Updated: 2023/11/18 15:33:51 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_len(char *num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i + 1] == '\0')
			return (-1);
		i++;
	}
	while (num[i] == '0')
		i++;
	while (num[i])
	{
		if (ft_isdigit(num[i]) == 0)
			return (-1);
		j++;
		i++;
	}
	return (j);
}

static int	check_int(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_len(argv[i]) > 10 || check_len(argv[i]) == -1 || \
		(long)ft_atol(argv[i]) < INT_MIN || (long)ft_atol(argv[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

static int	check_negative(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	parse(t_main *ph, int ac, char **av)
{
	if (!check_int(ac, av))
	{
		ft_putstr_fd("Invalid data type\n", 2);
		return (0);
	}
	if (!check_negative(ac, av))
	{
		ft_putstr_fd("Negative data\n", 2);
		return (0);
	}
	if ((ft_atoi(av[1]) == 0 || ft_atoi(av[2]) == 0 || ft_atoi(av[3]) == 0
			|| ft_atoi(av[4]) == 0) || (ac == 6 && ft_atoi(av[5]) == 0))
	{
		ft_putstr_fd("Null data\n", 2);
		return (0);
	}
	ph->nb_philo = ft_atoi(av[1]);
	ph->to_die = ft_atoi(av[2]);
	ph->to_eat = ft_atoi(av[3]);
	ph->to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph->max_meal = ft_atoi(av[5]);
	else
		ph->max_meal = 0;
	return (1);
}

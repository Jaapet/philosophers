/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:22:35 by ndesprez          #+#    #+#             */
/*   Updated: 2023/11/19 18:26:39 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) != 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_main	ph;

	ft_bzero(&ph, sizeof(ph));
	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments\n", 29), 1);
	if (!check_digit(ac, av))
		return (write(2, "Invalid format of arguments\n", 29), 1);
	if (!parse(&ph, ac, av))
		return (1);
	ph.true_time = get_time();
	if (ph.nb_philo == 1)
		printf("0         1         has taken a fork\n \
		%-9li 1         died\n", ph.to_die);
	else
		ft_init(&ph);
	return (0);
}

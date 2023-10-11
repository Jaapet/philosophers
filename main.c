/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:22:35 by ndesprez          #+#    #+#             */
/*   Updated: 2023/10/08 17:22:35 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_main	ph;

	// DO SOMETHING SPECIAL WHEN ONLY ONE PHILO
	ft_bzero(&ph, sizeof(ph));
	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments\n", 29), 1);
	if (parse(&ph, ac, av) == false) // CHECK SI IL Y A DES CHAR NON NUM
		return (1);
	ph.true_time = get_time();
	ft_init(&ph);
	return (0);
}

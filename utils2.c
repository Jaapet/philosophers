/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:24:23 by ndesprez          #+#    #+#             */
/*   Updated: 2023/10/08 17:24:23 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' \
	|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		out;
	int		is_neg;
	size_t	i;

	out = 0;
	i = 0;
	is_neg = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_neg = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		out = out * 10 + nptr[i] - '0';
		i++;
	}
	return (out * is_neg);
}

long	ft_atol(const char *nptr)
{
	long	out;
	int		is_neg;
	size_t	i;

	out = 0;
	i = 0;
	is_neg = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_neg = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		out = out * 10 + nptr[i] - '0';
		i++;
	}
	return ((long)(out * is_neg));
}

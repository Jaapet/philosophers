/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:37:13 by ndesprez          #+#    #+#             */
/*   Updated: 2023/11/18 15:56:07 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static time_t	ft_ts(t_thread *thread)
{
	return (get_time() - thread->info->true_time);
}

void	ft_print_log(t_thread *thread, enum e_status status)
{
	pthread_mutex_lock(&thread->info->m_print);
	if (check_death(thread))
		return ;
	if (status == fork_taken)
		printf("%-9lu %-9lu has taken a fork\n", ft_ts(thread), thread->id + 1);
	if (status == is_eating)
		printf("%-9lu %-9lu is eating\n", ft_ts(thread), thread->id + 1);
	if (status == is_sleeping)
		printf("%-9lu %-9lu is sleeping\n", ft_ts(thread), thread->id + 1);
	if (status == is_thinking)
		printf("%-9lu %-9lu is thinking\n", ft_ts(thread), thread->id + 1);
	if (status == dead)
	{
		if (pthread_mutex_lock(&thread->info->m_dead) == 0)
			thread->info->dead = 1;
		pthread_mutex_unlock(&thread->info->m_dead);
		printf("%-9lu %-9lu died\n", ft_ts(thread), thread->id + 1);
	}
	pthread_mutex_unlock(&thread->info->m_print);
}

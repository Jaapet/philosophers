/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:00:59 by ndesprez          #+#    #+#             */
/*   Updated: 2023/11/19 16:14:48 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	val;
	time_t			time;

	gettimeofday(&val, NULL);
	time = (val.tv_sec * 1000 + val.tv_usec / 1000);
	return (time);
}

void	ft_usleep(time_t us)
{
	time_t		end;

	end = get_time() + us / 1000;
	usleep(us / 1.25);
	while (get_time() < end)
		usleep(100);
}

void	check_time_to_eat(t_thread *thread)
{
	thread->time_to_eat = (get_time() - thread->info->true_time) \
		- thread->time_start;
}

int	check_death(t_thread *thread)
{
	if (pthread_mutex_lock(&thread->info->m_dead) == 0)
	{
		if (thread->info->dead)
		{
			pthread_mutex_unlock(&thread->info->m_dead);
			return (1);
		}
		pthread_mutex_unlock(&thread->info->m_dead);
	}
	pthread_mutex_lock(&thread->info->m_satiate);
	if (thread->info->satiate)
	{
		pthread_mutex_unlock(&thread->info->m_satiate);
		return (1);
	}
	pthread_mutex_unlock(&thread->info->m_satiate);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:51:23 by ndesprez          #+#    #+#             */
/*   Updated: 2023/11/19 16:20:02 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	t_routine_seq(t_thread *thread)
{
	if (check_death(thread))
		return (1);
	ft_usleep(thread->info->to_sleep * 999);
	if (check_death(thread))
		return (1);
	ft_print_log(thread, is_thinking);
	if (check_death(thread))
		return (1);
	return (0);
}

static void	eating_routine(t_thread *thread, size_t id, t_main *info)
{
	if (id + 1 == info->nb_philo)
		id = -1;
	if (pthread_mutex_lock(&(info->threads[thread->id]->m_fork)) == 0)
	{
		ft_print_log(thread, fork_taken);
		if (pthread_mutex_lock(&(info->threads[id + 1]->m_fork)) == 0)
		{
			if (pthread_mutex_lock(&thread->m_time_start) == 0)
				thread->time_start = (get_time() - info->true_time);
			pthread_mutex_unlock(&thread->m_time_start);
			ft_print_log(thread, is_eating);
			ft_usleep(info->to_eat * 1000);
		}
	}
	pthread_mutex_unlock(&(info->threads[thread->id]->m_fork));
	pthread_mutex_unlock(&(info->threads[id + 1]->m_fork));
	pthread_mutex_lock(&thread->m_meal_count);
	thread->meal_count++;
	pthread_mutex_unlock(&thread->m_meal_count);
	check_time_to_eat(thread);
}

void	*t_routine(void *arg)
{
	t_thread	*current;

	current = (t_thread *)arg;
	if (current->id % 2)
	{
		ft_print_log(current, is_thinking);
		ft_usleep(current->info->to_eat * 1000);
	}
	while (!check_death(current))
	{
		if (check_death(current))
			break ;
		eating_routine(current, current->id, current->info);
		if (check_death(current))
			break ;
		ft_print_log(current, is_sleeping);
		if (t_routine_seq(current))
			break ;
		if (check_death(current))
			break ;
	}
	return (0);
}

static int	w_routine_sat(t_main *info, size_t count, size_t i)
{
	static size_t	count_bis = 0;

	if (count == 0)
		count_bis = 0;
	pthread_mutex_lock(&info->threads[i]->m_meal_count);
	if (info->max_meal != 0 && (info->threads[i]->meal_count) >= info->max_meal)
		count_bis++;
	if ((i + 1) == info->nb_philo && count_bis == info->nb_philo)
	{
		pthread_mutex_lock(&info->m_satiate);
		info->satiate = 1;
		pthread_mutex_unlock(&info->m_satiate);
		pthread_mutex_unlock(&info->threads[i]->m_meal_count);
		return (1);
	}
	pthread_mutex_unlock(&info->threads[i]->m_meal_count);
	return (0);
}

void	*w_routine(void *arg)
{
	t_main	*info;
	size_t	i;

	info = (t_main *)arg;
	while (1)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			info->cur_time = (get_time() - info->true_time);
			pthread_mutex_lock(&info->threads[i]->m_time_start);
			if ((info->cur_time - info->threads[i]->time_start) >= info->to_die)
			{
				pthread_mutex_unlock(&info->threads[i]->m_time_start);
				ft_print_log(info->threads[i], dead);
				return (0);
			}
			pthread_mutex_unlock(&info->threads[i]->m_time_start);
			if (w_routine_sat(info, i, i))
				return (0);
			i++;
		}
	}
}

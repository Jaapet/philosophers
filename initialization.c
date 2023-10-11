/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:40:49 by ndesprez          #+#    #+#             */
/*   Updated: 2023/10/11 15:40:49 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_watcher(t_main *ph)
{
	if (pthread_create(&ph->watcher_id, NULL, ft_routine_watcher, ph))
		return (ft_putstr_fd("Thread creation error", 2), exit(1));
}

static void	init_thread(t_main *ph, size_t thread_index)
{
	t_thread	*current;

	current = ft_calloc(1, sizeof(t_thread));
	if (current == NULL)
		exit(1);
	ph->threads[thread_index] = current;
	current->info = ph;
	current->id = thread_index;
	pthread_mutex_init(&(current->m_fork), NULL);
	pthread_mutex_init(&(current->m_time_start), NULL);
	pthread_mutex_init(&(current->m_meal_count), NULL);
}

void	ft_init(t_main *ph)
{
	size_t	i;

	ph->threads = ft_calloc(ph->nb_philo + 1, sizeof(t_thread)); // caloc fumeux
	pthread_mutex_init(&(ph->m_dead), NULL);
	pthread_mutex_init(&(ph->m_satiate), NULL);
	pthread_mutex_init(&(ph->m_log_print), NULL);
	i = 0;
	while (i < ph->nb_philo)
	{
		init_thread(ph, i);
		i++;
	}
	i = 0;
	while (i < ph->nb_philo)
	{
		if (pthread_create(&ph->threads[i]->thread_id, NULL, t_routine, ph->threads[i]))
			return (ft_putstr_fd("Thread creation error", 2), exit(1));
		i++;
	}
	init_watcher(ph);
	i = 0;
	while (i < ph->nb_philo)
	{
		pthread_join(ph->threads[i]->thread_id, NULL);
		i++;
	}
	pthread_join(ph->watcher_id, NULL);
}

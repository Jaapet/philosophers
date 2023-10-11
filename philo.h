/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:15:32 by ndesprez          #+#    #+#             */
/*   Updated: 2023/10/08 17:15:32 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

enum	e_status
{
	unknown,
	fork_taken,
	is_eating,
	is_sleeping,
	is_thinking,
	dead
};

typedef struct s_thread
{
	pthread_t		thread_id;
	size_t			id;
	pthread_mutex_t	m_fork;
	size_t			meal_count;
	pthread_mutex_t	m_meal_count;
	struct s_main	*info;
	time_t			time_start;
	pthread_mutex_t	m_time_start;
	time_t			time_to_eat;
}	t_thread;

typedef struct s_main
{
	size_t			nb_philo;
	size_t			max_meal;
	time_t			to_die;
	time_t			to_eat;
	time_t			to_sleep;
	time_t			true_time;
	time_t			cur_time;
	bool			dead;
	pthread_mutex_t	m_dead;
	bool			satiate;
	pthread_mutex_t	m_satiate;
	t_thread		**threads;
	pthread_t		whatcher_id;
	pthread_mutex_t	m_print;
}	t_main;

/*----UTILS----*/
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t count, size_t size);

#endif

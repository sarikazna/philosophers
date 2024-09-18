/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:40:19 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 15:27:01 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Trying to make the system fair. */
void	de_synchronize_philos(t_philo *philo)
{
	if (philo->sim->philo_nbr % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			precise_usleep(3e4, philo->sim);
	}
	else
	{
		if (philo->philo_id % 2)
			thinking(philo, true);
	}
}

/* Spinlock to synchronize philosophers start */
void	wait_all_threads(t_sim *sim)
{
	while (!get_bool(&sim->table_mutex, &sim->all_threads_ready))
		;
}

/* Monitor busy waits until all threads are running*/
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/* Increase threads running to synchro with the monitor */
void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

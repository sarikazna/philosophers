/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:19:08 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 15:52:25 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Another wrapper function to avoid writing LOCK and UNLCK everywhere. The
differentiation comes with data types - bool and long */

/* Bool */
void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	// READING thread save
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/* Long */
void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/* Simulation finished. The purpose of it is to make the code look
cleaner/ more readable.*/
bool	sim_finished(t_sim *sim)
{
	return (get_bool(&sim->table_mutex, &sim->end_sim));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:12:07 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 13:54:33 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_sim *sim)
{
	t_philo *philo;
	int	i;

	i = -1;
	while(++i < sim->philo_nbr)
	{
		philo = sim->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&sim->write_mutex, DESTROY);
	safe_mutex_handle(&sim->write_mutex, DESTROY);
	free(sim->spoons);
	free(sim->philos);
}

/* Get time of day time_code -> SECONDS MILISECONDS MICROSECONS */
long	gettime(t_time_code time_code)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		error_exit("Get time of day failed.");
	if (time_code == SECOND)
		return(tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime");
	return (-1);
}

/* Precise usleep function. usleep() itself is not precise enough. */
void	precise_usleep(long usec, t_sim *sim)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		// 1)
		if (sim_finished(sim))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		remaining = usec - elapsed;

		// to get a spinklock threshod
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			// SPINLOCK
			while(gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

// TO DO, check if anything needs to be freed and add the *sim into the function

/* Writes the error and exits the program. */
void	error_exit(const char *error)
{
	printf(RED"Error: %s\n"RST, error);
	exit(EXIT_FAILURE);
}

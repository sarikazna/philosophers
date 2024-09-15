/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:12:07 by srudman           #+#    #+#             */
/*   Updated: 2024/09/15 16:18:13 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Get time of day
time_code -> SECONDS MICROSECONS */
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
}

// TO DO, check if anything needs to be freed and add the *sim into the function

/* Writes the error and exits the program. */
void	error_exit(const char *error)
{
	printf(RED"Error: %s\n"RST, error);
	exit(EXIT_FAILURE);
}

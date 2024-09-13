/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:40:16 by srudman           #+#    #+#             */
/*   Updated: 2024/09/13 18:47:31 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for usleep
#include <stdbool.h>
#include <pthread.h> //mutex: init destroy lock unlock
					// threads: create join detach
#include <sys/time.h> // gettimeofday
#include <limits.h> // INT_MAX, INT_MIN

/* DEFINITIONS */


/* STRUCTURES */

struct s_spoon
{
	
};


struct s_philo
{
	int		id;
	long	meals_count;
	bool	is_satiated;
	long	last_meal_time; //time passed from last meal
}	t_philo;





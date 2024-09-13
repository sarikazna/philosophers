/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:40:16 by srudman           #+#    #+#             */
/*   Updated: 2024/09/13 19:07:57 by srudman          ###   ########.fr       */
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

typedef	pthread_mutex_t	t_mtx;
typedef	struct s_sim	t_sim;

/* STRUCTURES */

typedef struct s_spoon
{
	t_mtx	spoon;
	int		spoon_id;
}			t_spoon;

typedef struct s_philo
{
	int			philo_id;
	long		meals_count;
	bool		is_satiated;
	long		last_meal_time; //time passed from last meal
	t_spoon		*left_spoon;
	t_spoon		*right_spoon;
	pthread_t	thread_id; // a philo is a thread
	t_sim		*sim;
}				t_philo;

struct s_sim
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_sim;
	bool	end_sim; //a philo dies or all philos full
	t_spoon	*spoons; // array to spoons
	t_philo	*philos;
}			t_sim;






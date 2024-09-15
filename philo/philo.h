/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:40:16 by srudman           #+#    #+#             */
/*   Updated: 2024/09/15 16:11:51 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> // for usleep
# include <stdbool.h>
# include <pthread.h> //mutex: init destroy lock unlock
					// threads: create join detach
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX, INT_MIN
# include <errno.h>

/* DEFINITIONS */

// Colours
# define RST	"\033[0m"
# define RED	"\033[1;31m"

// Enum for time code and mutex/threads code

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;


typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}				t_opcode;

// Short version of data type
typedef pthread_mutex_t	t_mtx;

/* STRUCTURES */

// Name of struct for the recursive action
typedef struct s_sim	t_sim;

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
	t_spoon		*first_spoon;
	t_spoon		*second_spoon;
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
	bool	all_threads_ready;
	t_mtx	table_mutex; // avoid races while reading from table
	t_spoon	*spoons; // array to spoons
	t_philo	*philos;
};

/* FUNCTION PROTOTYPES */

void	error_exit(const char *error);
void	*safe_malloc(size_t bytes);
void	safe_thread_handle(pthread_t *thread, void *(foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
long	ft_atol(const char *nptr);
void	check_input(int ac, char **av);
void	parse_input(t_sim *sim, char **av);
void	sim_init(t_sim *sim);
void	sim_init2(t_sim *sim);
void	philos_init(t_sim *sim);
void	spoons_init(t_sim *sim);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	sim_finished(t_sim *sim);
void	wait_all_threads(t_sim *sim);

#endif
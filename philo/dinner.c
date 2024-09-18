/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:37 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 15:14:45 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// argument should be like this: ./philo 5 1000 200 200 5

void	thinking(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	
	if(!pre_sim)
		write_status(THINKING, philo);
	if (philo->sim->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->sim->time_to_eat;
	t_sleep = philo->sim->time_to_sleep;
	t_think = t_eat * 2 - t_sleep; // avialble time to think
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.31, philo->sim);
}

// If we only get a single philo
// LEFT OFF at 1>47>34 https://www.youtube.com/watch?v=zOpzGHwJ3MU&t=1353s

void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->sim);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->sim->table_mutex, &philo->sim->threads_running_nbr);
	write_status(TAKE_FIRST_SPOON, philo);
	while (!sim_finished(philo->sim))
		usleep(200);
	return(NULL);
}

static void	eat(t_philo *philo)
{
	// Grabbing the forks
	safe_mutex_handle(&philo->first_spoon->spoon, LOCK);
	write_status(TAKE_FIRST_SPOON, philo);
	safe_mutex_handle(&philo->second_spoon->spoon, LOCK);
	write_status(TAKE_SECOND_SPOON, philo);

	// Write eat
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo);
	precise_usleep(philo->sim->time_to_eat, philo->sim);
	if (philo->sim->nbr_limit_meals > 0
		&& philo->meals_count == philo->sim->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->is_satiated, true);
	
	// Unlocking the forks
	safe_mutex_handle(&philo->first_spoon->spoon, UNLOCK);
	safe_mutex_handle(&philo->second_spoon->spoon, UNLOCK);
}


void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	//spinlock
	wait_all_threads(philo->sim); // All the philosophers will wait for the threads to be ready
	
	// set time last meal
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	
	// synchro with monitor
	// increase a sim variable counter, with all threads running
	increase_long(&philo->sim->table_mutex, &philo->sim->threads_running_nbr);
	
	// desychronizing philos
	de_synchronize_philos(philo);

	while (!sim_finished(philo->sim)) // till end of simulation
	{
		// 1) am I full?
		if (philo->is_satiated) // TO DO thread safe?
			break ;
		
		// 2) eat
		eat(philo);

		// 3) sleep, write_status & pricise usleep
		write_status(SLEEPING, philo);
		precise_usleep(philo->sim->time_to_sleep, philo->sim);
		
		// 4) think
		thinking(philo, false); //TO DO
	}

	return (NULL);
}

/* Dinner starts if the number of meals is larger than 1.
1. If we only have one philosopher, we only have one spoon so he won't
be able to eat.
2. Monitor thread checking if a philosopher is dead
3. Synchromize the beginning of the symulation. 
4. Join everyone. */
void	dinner_start(t_sim *sim)
{
	int	i;

	i = -1;
	if (sim->nbr_limit_meals == 0)
		return ;// back to main and clean
	else if (sim->philo_nbr == 1)
	{
		safe_thread_handle(&sim->philos[0].thread_id, single_philo, &sim->philos[0], CREATE);
	}
	else
	{
		//This while loop will create all the threads, so allthe philosophers
		while (++i < sim->philo_nbr)
			safe_thread_handle(&sim->philos[i].thread_id, dinner_sim,
				&sim->philos[i], CREATE);
	}
	// monitor
	safe_thread_handle(&sim->monitor, monitor_dinner, sim, CREATE); // TO DO
	// start of simulation
	sim->start_sim = gettime(MILLISECOND);
	
	// now all threads are ready!
	set_bool(&sim->table_mutex, &sim->all_threads_ready, true);

	// wait for everyone
	i = -1;
	while (++i < sim->philo_nbr)
		safe_thread_handle(&sim->philos[i].thread_id, NULL, NULL, JOIN);
	// If we manage to reach this line, all philosophers are full.
	set_bool(&sim->table_mutex, &sim->end_sim, true);
	safe_thread_handle(&sim->monitor, NULL, NULL, JOIN);
}

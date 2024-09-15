/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:37 by srudman           #+#    #+#             */
/*   Updated: 2024/09/15 19:15:02 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// argument should be like this: ./philo 5 1000 200 200 5
// LEFT OFF at 1:29 https://www.youtube.com/watch?v=zOpzGHwJ3MU&t=1353s

// TO DO
static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}


static void	eat(t_philo *philo)
{
	// Grabbing the forks
	safe_mutex_handle(&philo->first_spoon->spoon, LOCK);
	write_status(TAKE_FIRST_SPOON, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_spoon->spoon, LOCK);
	write_status(TAKE_SECOND_SPOON, philo, DEBUG_MODE);

	// Write eat
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MODE);
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
	
	// set last meal time

	while (!sim_finished(philo->sim)) // till end of simulation
	{
		// 1) am I full?
		if (philo->is_satiated) // TO DO thread safe?
			break ;
		
		// 2) eat
		eat(philo);

		// 3) sleep, write_status & pricise usleep
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->sim->time_to_sleep, philo->sim);
		
		// 4) think
		thinking(philo); //TO DO
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

	i = -i;
	if (sim->nbr_limit_meals <= 0)
		return ;// back to main and clean
	else if (sim->philo_nbr == 1)
	{
		// TO DO
	}
	else
	{
		//This while loop will create all the threads, so allthe philosophers
		while (++i < sim->philo_nbr)
			safe_thread_handle(&sim->philos[i].thread_id, dinner_sim,
				&sim->philos[i], CREATE);
	}
	// start of simulation
	sim->start_sim == gettime(MILLISECOND);
	
	// now all threads are ready!
	set_bool(&sim->table_mutex, &sim->all_threads_ready, true);

	// wait for everyone
	i = -1;
	while (++i < sim->philo_nbr)
		safe_thread_handle(&sim->philos[i].thread_id, NULL, NULL, JOIN);
	// If we manage to reach this line, all philosophers are full.
}

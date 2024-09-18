/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:37 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 20:58:03 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// argument should be like this: ./philo 5 1000 200 200 5

void	thinking(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, philo);
	if (philo->sim->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->sim->time_to_eat;
	t_sleep = philo->sim->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.31, philo->sim);
}

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
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_spoon->spoon, LOCK);
	write_status(TAKE_FIRST_SPOON, philo);
	safe_mutex_handle(&philo->second_spoon->spoon, LOCK);
	write_status(TAKE_SECOND_SPOON, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo);
	precise_usleep(philo->sim->time_to_eat, philo->sim);
	if (philo->sim->nbr_limit_meals > 0
		&& philo->meals_count == philo->sim->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->is_satiated, true);
	safe_mutex_handle(&philo->first_spoon->spoon, UNLOCK);
	safe_mutex_handle(&philo->second_spoon->spoon, UNLOCK);
}

void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->sim);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->sim->table_mutex, &philo->sim->threads_running_nbr);
	de_synchronize_philos(philo);
	while (!sim_finished(philo->sim))
	{
		if (philo->is_satiated)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->sim->time_to_sleep, philo->sim);
		thinking(philo, false);
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
		return ;
	else if (sim->philo_nbr == 1)
	{
		safe_thread_handle(&sim->philos[0].thread_id, single_philo,
			&sim->philos[0], CREATE);
	}
	else
	{
		while (++i < sim->philo_nbr)
			safe_thread_handle(&sim->philos[i].thread_id, dinner_sim,
				&sim->philos[i], CREATE);
	}
	safe_thread_handle(&sim->monitor, monitor_dinner, sim, CREATE);
	sim->start_sim = gettime(MILLISECOND);
	set_bool(&sim->table_mutex, &sim->all_threads_ready, true);
	i = -1;
	while (++i < sim->philo_nbr)
		safe_thread_handle(&sim->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&sim->table_mutex, &sim->end_sim, true);
	safe_thread_handle(&sim->monitor, NULL, NULL, JOIN);
}

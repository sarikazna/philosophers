/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:05:00 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 15:50:55 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->is_satiated))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->sim->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

// left off at 1>42>30
void	*monitor_dinner(void *data)
{
	int		i;
	t_sim	*sim;

	sim = (t_sim *)data;
	if (sim->philo_nbr == 1)
	{
		while (!sim_finished(sim))
		{
			if (philo_died(sim->philos))
			{
				set_bool(&sim->table_mutex, &sim->end_sim, true);
				write_status(DIED, sim->philos);
			}
			usleep(200); // Avoid busy-waiting
		}
		return (NULL);
	}
	// be sure that all philos are running. We wait with while
	// spinlock till all threads run
	while (!all_threads_running(&sim->table_mutex, &sim->threads_running_nbr,
			sim->philo_nbr))
		;
	while (!sim_finished(sim))
	{
		i = -1;
		while (++i < sim->philo_nbr && !sim_finished(sim))
		{
			if (philo_died(sim->philos + 1)) // TO DO
			{
				set_bool(&sim->table_mutex, &sim->end_sim, true);
				write_status(DIED, sim->philos + 1);
			}
		}
	}
	return (NULL);
}

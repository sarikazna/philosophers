/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:05:00 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 23:36:34 by srudman          ###   ########.fr       */
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

bool	single_philo_check(t_sim *sim)
{
	if (sim->philo_nbr == 1)
	{
		while (!sim_finished(sim))
		{
			if (philo_died(sim->philos))
			{
				set_bool(&sim->table_mutex, &sim->end_sim, true);
				write_status(DIED, sim->philos);
			}
			usleep(200);
		}
		return (0);
	}
	return (1);
}

bool	all_philos_full(t_sim *sim)
{
	int	count_full_philos;
	int	i;

	i = -1;
	count_full_philos = 0;
	//safe_mutex_handle(&sim->table_mutex, LOCK);
	while (++i < sim->philo_nbr && !sim_finished(sim))
	{
		safe_mutex_handle(&sim->philos[i].philo_mutex, LOCK);
		if (sim->philos[i].is_satiated == true)
			count_full_philos++;
		//printf("#%i Philo, Statiation: %i\n", sim->philos[i].philo_id, sim->philos[i].is_satiated);
		safe_mutex_handle(&sim->philos[i].philo_mutex, UNLOCK);
	}
	//safe_mutex_handle(&sim->table_mutex, UNLOCK);
	if (sim->philo_nbr == count_full_philos)
	{
		set_bool(&sim->table_mutex, &sim->end_sim, true);
		return (1);
	}
	else
		return (0);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_sim	*sim;

	sim = (t_sim *)data;
	if (!single_philo_check(sim))
		return (NULL);
	while (!all_threads_running(&sim->table_mutex, &sim->threads_running_nbr,
			sim->philo_nbr))
		; // potential problem
	while (!sim_finished(sim))
	{
		i = -1;
		while (++i < sim->philo_nbr && !sim_finished(sim))
		{
			// if (philo_died(sim->philos + 1))
			// {
			// 	set_bool(&sim->table_mutex, &sim->end_sim, true);
			// 	write_status(DIED, sim->philos + 1);
			// }
			    if (philo_died(&sim->philos[i])) 
				{
     	 			set_bool(&sim->table_mutex, &sim->end_sim, true);
       				write_status(DIED, &sim->philos[i]);
				}
		}
		if (sim->nbr_limit_meals > 0 && all_philos_full(sim))
		{
			set_bool(&sim->table_mutex, &sim->end_sim, true);
			return (NULL);
		}
	}
	return (NULL);
}

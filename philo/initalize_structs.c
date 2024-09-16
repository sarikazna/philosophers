/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalize_structs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:25:05 by srudman           #+#    #+#             */
/*   Updated: 2024/09/16 17:31:14 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Even and odd spoon assignment */
static void	assign_spoons(t_philo *philo, t_spoon *spoons, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->sim->philo_nbr;
	philo->second_spoon = &spoons[philo_position];
	philo->first_spoon = &spoons[(philo_position + 1) % philo_nbr];
	if (philo->philo_id % 2 == 0 == 0)
	{
		philo->first_spoon = &spoons[philo_position];
		philo->second_spoon = &spoons[(philo_position + 1) % philo_nbr];
	}
}

void	philos_init(t_sim *sim)
{
	int		i;
	t_philo	*philo;

	sim->philos = safe_malloc(sizeof(t_philo) * sim->philo_nbr);
	i = -1;
	while (++i < sim->philo_nbr)
	{
		philo = sim->philos + i;
		philo->philo_id = i + 1;
		philo->meals_count = 0;
		philo->is_satiated = false;
		philo->sim = sim;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_spoons(philo, sim->spoons, i);
	}
}

void	spoons_init(t_sim *sim)
{
	int	i;

	i = -1;
	sim->spoons = safe_malloc(sizeof(t_spoon) * sim->philo_nbr);
	while (++i < sim->philo_nbr)
	{
		safe_mutex_handle(&sim->spoons[i].spoon, INIT);
		sim->spoons[i].spoon_id = i;
	}
}

void	sim_init2(t_sim *sim)
{
	safe_mutex_handle(&sim->table_mutex, INIT);
	safe_mutex_handle(&sim->write_mutex, INIT);
}

void	sim_init(t_sim *sim)
{
	sim = safe_malloc(sizeof(t_sim));
	sim->philo_nbr = -1;
	sim->time_to_die = -1;
	sim->time_to_eat = -1;
	sim->time_to_sleep = -1;
	sim->nbr_limit_meals = -1;
	sim->threads_running_nbr = 0;
	sim->end_sim = false;
	sim->all_threads_ready = false;
}

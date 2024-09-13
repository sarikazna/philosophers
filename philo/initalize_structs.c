/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:25:05 by srudman           #+#    #+#             */
/*   Updated: 2024/09/13 21:37:34 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_init(t_sim *sim)
{
	sim = malloc(sizeof(t_sim));
	if (sim == NULL)
	{
		error_exit("Memory allocation failed");
		return ;
	}
	sim->philo_nbr = -1;
	sim->time_to_die = -1;
	sim->time_to_eat = -1;
	sim->time_to_sleep = -1;
	sim->nbr_limit_meals = -1;
	sim->end_sim = false;
	// INIT spoons
	// INIT philos
}
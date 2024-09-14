/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:22:25 by srudman           #+#    #+#             */
/*   Updated: 2024/09/14 20:55:30 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_sim *sim, char **av)
{
	sim->philo_nbr = ft_atol(av[1]);
	sim->time_to_die = ft_atol(av[2]) * 1000;
	sim->time_to_eat = ft_atol(av[3]) * 1000;
	sim->time_to_sleep = ft_atol(av[4]) * 1000;
	if (sim->time_to_die < 60000 || sim->time_to_eat < 60000
		|| sim->time_to_sleep < 60000)
		error_exit("The timestamps should be 60ms or higher.");
	if (av[5])
		sim->nbr_limit_meals = ft_atol(av[5]);
	philos_init(sim);
	spoons_init(sim);
}

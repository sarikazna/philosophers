/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:45:37 by srudman           #+#    #+#             */
/*   Updated: 2024/09/14 20:59:41 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// argument should be like this: ./philo 5 1000 200 200 5
// LEFT OFF at 57:00 https://www.youtube.com/watch?v=zOpzGHwJ3MU&t=1353s

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(); // TO DO for synchronisation
	return (NULL);
}

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
}

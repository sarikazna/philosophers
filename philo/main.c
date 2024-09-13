/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:09:20 by srudman           #+#    #+#             */
/*   Updated: 2024/09/13 22:06:38 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// argument should be like this: ./philo 5 1000 200 200 5
// Left off in parsing.c
int	main(int ac, char **av)
{
	t_sim	sim;
	
	if (ac != 5 && ac != 6)
		error_exit("Wrong input\n");
	check_input(ac, av);
	sim_init(&sim);
	parse_input(&sim, av);
	start_dinner(&sim);
	clean_all(&sim); // philos full or 1 philo died
}
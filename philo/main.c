/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:09:20 by srudman           #+#    #+#             */
/*   Updated: 2024/09/17 21:06:51 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Left off in dinner.c
int	main(int ac, char **av)
{
	t_sim	sim;

	if (ac != 5 && ac != 6)
		error_exit("Wrong input\n");
	check_input(ac, av);
	sim_init(&sim);
	parse_input(&sim, av);
	dinner_start(&sim); // you need to initialize the max_number of meals = ft_atoi(av[5])
	clean_all(&sim); // philos full or 1 philo died
}

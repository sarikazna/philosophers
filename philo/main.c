/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:09:20 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 20:58:25 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_sim	sim;

	if (ac != 5 && ac != 6)
		error_exit("Wrong input\n");
	check_input(ac, av);
	sim_init(&sim);
	parse_input(&sim, av);
	dinner_start(&sim);
	clean_all(&sim);
}

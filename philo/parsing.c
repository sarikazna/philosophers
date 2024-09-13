/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:22:25 by srudman           #+#    #+#             */
/*   Updated: 2024/09/13 22:06:18 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Converts a string into a 'long'. It works exactly like atoi but
instead of converting it into an int, it converts it into a long */
long	ft_long_atoi(const char *nptr)
{
	long	nb;
	int		minus;

	nb = 0;
	minus = 1;
	while (*nptr != '\0')
	{
		while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
			nptr++;
		if (*nptr == '+' || *nptr == '-')
		{
			if (*nptr == '-')
				minus = -1;
			nptr++;
		}
		while (*nptr >= '0' && *nptr <= '9')
		{
			nb = nb * 10 + (*nptr - '0');
			nptr++;
		}
		break ;
	}
	return (nb * minus);
}
// TO DO: Ensure they're not bigger than INT_MAX
// Left off at 22:33 https://www.youtube.com/watch?v=zOpzGHwJ3MU&t=937s

void	parse_input(t_sim *sim, char **av)
{
	sim->philo_nbr = ft_long_atoi(av[1]);
	sim->time_to_die = ft_long_atoi(av[2]);
	sim->time_to_eat = ft_long_atoi(av[3]);
	sim->time_to_sleep = ft_long_atoi(av[4]);
	if (av[5])
		sim->nbr_limit_meals = ft_long_atoi(av[5]);
	// INIT spoons and parse them
	// INIT philos and parse them
}
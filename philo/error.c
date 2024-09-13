/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:12:07 by srudman           #+#    #+#             */
/*   Updated: 2024/09/13 21:33:13 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Checks that arguments are numerical as a typical program arguments would
be: ./philo 5 1000 200 200 5 */

// TO DO, also add in '+'
int		is_numerical(char *av)
{
	int	i;
	
	i = 0;
	while(av[i])
	{
		if (av[i] <= '0' || av[i] >= '9')
			return (0);
		i++;
	}
	return (1);
}

/* Checks that arguments exist, i.e., makes sure there are 
no null arguments or non numerical arguments */
void	check_input(int ac, char **av)
{
	int	i;
	
	i = ac - 1;
	while (i > 0)
	{
		if (!av[i] || !is_numerical(av[i]))
			error_exit("Wrong input");
		i--;
	}
}

/* Writes the error and exits the program */
void	error_exit(const char *error)
{
	printf(RED"Error: %s\n"RST, error);
	exit(EXIT_FAILURE);
}
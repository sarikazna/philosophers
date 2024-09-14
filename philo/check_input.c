/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:49:23 by srudman           #+#    #+#             */
/*   Updated: 2024/09/14 16:49:09 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Converts a string into a 'long'. It works exactly like atoi but
instead of converting it into an int, it converts it into a long */
long	ft_atol(const char *nptr)
{
	long	nb;

	nb = 0;
	while (*nptr != '\0')
	{
		while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
			nptr++;
		if (*nptr == '+')
			nptr++;
		while (*nptr >= '0' && *nptr <= '9')
		{
			nb = nb * 10 + (*nptr - '0');
			nptr++;
		}
		break ;
	}
	return (nb);
}

/* Checks that argument is a positive number. A valid number can be 
"     +366fg", so the bumber is 366. It also has to be smaller than INT_MAX. */
int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			i++;
		if (str[i] == '+')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (ft_atol(str) <= INT_MAX)
				return(1);
			else
				return(0);
		}
		else
			return(0);
	}
	return(0);
}

/* Checks that arguments exist, i.e., makes sure there are 
no null arguments or non numerical arguments. */
void	check_input(int ac, char **av)
{
	int	i;
	
	i = ac - 1;
	while (i > 0)
	{
		if (!av[i] || !is_valid_number(av[i]))
			error_exit("Wrong input");
		i--;
	}
}
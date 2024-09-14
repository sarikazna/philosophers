/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:12:07 by srudman           #+#    #+#             */
/*   Updated: 2024/09/14 20:55:16 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TO DO, check if anything needs to be freed and add the *sim into the function

/* Writes the error and exits the program. */
void	error_exit(const char *error)
{
	printf(RED"Error: %s\n"RST, error);
	exit(EXIT_FAILURE);
}

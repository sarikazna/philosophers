/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:40:19 by srudman           #+#    #+#             */
/*   Updated: 2024/09/15 15:46:50 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Spinlock to synchronize philosophers start */
void	wait_all_threads(t_sim *sim)
{
	while(!get_bool(&sim->table_mutex, &sim->all_threads_ready))
	;
}

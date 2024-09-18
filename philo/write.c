/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:11:07 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 15:16:06 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->sim->start_sim;
	if (philo->is_satiated)
		return ;
	safe_mutex_handle(&philo->sim->write_mutex, LOCK);
	if ((status == TAKE_FIRST_SPOON || status == TAKE_SECOND_SPOON)
		&& !sim_finished(philo->sim))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->philo_id);
	else if (status == EATING && !sim_finished(philo->sim))
		printf("%-6ld %d is eating\n", elapsed, philo->philo_id);
	else if (status == SLEEPING && !sim_finished(philo->sim))
		printf("%-6ld %d is sleeping\n", elapsed, philo->philo_id);
	else if (status == THINKING && !sim_finished(philo->sim))
		printf("%-6ld %d is thinking\n", elapsed, philo->philo_id);
	else if (status == DIED)
		printf(RED"%-6ld %d died\n"RST, elapsed, philo->philo_id);
	safe_mutex_handle(&philo->sim->write_mutex, UNLOCK);
}

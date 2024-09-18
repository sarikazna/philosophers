/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srudman <srudman@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:57:25 by srudman           #+#    #+#             */
/*   Updated: 2024/09/18 21:00:32 by srudman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* MALLOC SAFE wrapper function*/
/* Malloc but putting the safeguards in there so to shorten the code in
other functions.*/
void	*safe_malloc(size_t bytes)
{
	void	*return_ptr;

	return_ptr = malloc(bytes);
	if (return_ptr == NULL)
		error_exit("Memory allocation failed.");
	return (return_ptr);
}

/* Handling the error return values of mutex functions. */
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread blocked waiting for \
			mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate enough memory to create \
			another mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

/* One function to handle mutex functions. */
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode.");
}

/* THREADS Wrapper Functions */
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("Insufficient resources to create another thread.");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("Insufficient resources to create another thread.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified is not a joinable thread.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of thread \
		specifies the calling thread.");
	else if (status == EPERM)
		error_exit("No permission to set the scheduling policy and \
		parameters specified in attr.");
	else if (status == ESRCH)
		error_exit("No thread with the ID thread could be found.");
}

// Wrapper of the treads function to make the code cleaner.
void	safe_thread_handle(pthread_t *thread, void *(foo)(void *),
	void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle: use \
			<CREATE> <JOIN> <HANDLE>");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:49 by codespace         #+#    #+#             */
/*   Updated: 2024/09/26 20:26:44 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/philosophers.h"

void	*ft_safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		ft_error_exit("Error with the malloc");
	return (ret);
}

static void	ft_handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		ft_error_exit("The value specified by mutex is invalid.");
	else if (EINVAL == status && (INIT == opcode || DESTROY == opcode))
		ft_error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		ft_error_exit("A deadlock would occur if the thread \
		blocked waiting for mutex.");
	else if (EPERM == status)
		ft_error_exit("The current thread does not hold a lock on mmutex.");
	else if (ENOMEM == status)
		ft_error_exit("The process cannot allocate enough memory \
		to create another mutex.");
	else if (EBUSY == status)
		ft_error_exit("Mutex is locked");
}

void	ft_safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		ft_handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		ft_handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		ft_handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		ft_handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		ft_error_exit("Wrong opcode for mutex handle");
}

static void	ft_handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		ft_error_exit("No resources to create another thread.");
	else if (EPERM == status)
		ft_error_exit("The caller does not have appropriate premission.\n");
	else if (EINVAL == status)
		ft_error_exit("The valeu specified by attr is invalid.");
	else if (EINVAL == status)
		ft_error_exit("The valeu specified by thread is not joinable.\n");
	else if (ESRCH == status)
		ft_error_exit("No thread could be found corresponding to tha.");
	else if (EDEADLK == status)
		ft_error_exit("A deadlock was detected or the value of" \
						"thread specifies the calling thread");
}

void	ft_safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		ft_handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		ft_handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		ft_handle_thread_error(pthread_detach(*thread), opcode);
	else
		ft_error_exit("Wrong opcode for thread_handle:" \
						" use <CREATE> <JOIN> <DETACH>");
}

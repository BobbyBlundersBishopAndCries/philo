/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:13 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/09 13:27:24 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void mutex_perror(int status, t_code code)
{
    if (0 == status)
        return;

    if (EINVAL == status && (LOCK == code || UNLOCK == code))
        error_exit("The value specified by mutex is invalid.");
    else if (EINVAL == status && INIT == code)
        error_exit("The value specified by attr is invalid.");
    else if (EDEADLK == status)
        error_exit("A deadlock would occur if the thread blocked waiting for mutex.");
    else if (EPERM == status)
        error_exit("The current thread does not hold a lock on mutex.");
    else if (ENOMEM == status)
        error_exit("The process cannot allocate enough memory to create another mutex.");
    else if (EBUSY == status)
        error_exit("Mutex is locked");
}

void	safe_mutex(t_mtx *mutex, t_code code)
{
	if (code == LOCK)
		mutex_perror(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		mutex_perror(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		mutex_perror(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		mutex_perror(pthread_mutex_destroy(mutex), code);
	else
		error_exit("wrong mutex code handle");
}

static void thread_perror(int status, t_code code)
{
    if (0 == status)
        return ;
    if (EAGAIN == status)
        error_exit("No resources to create another thread");
    else if (EPERM == status)
        error_exit("The caller does not have appropriate permission\n");
    else if (EINVAL == status && CREATE == code)
        error_exit("The value specified by attr is invalid.");
    else if (EINVAL == status && (JOIN == code || DETACH == code))
        error_exit("The value specified by thread is not joinable\n");
    else if (ESRCH == status)
        error_exit("No thread could be found corresponding to that specified by the given thread ID, thread.");
    else if (EDEADLK == status)
        error_exit("A deadlock was detected or the value of thread specifies the calling thread.");
}

void safe_thread(pthread_t *thread, void *( *routine)(void *),
    void *data, t_code code)
{
    if (CREATE == code)
        thread_perror(pthread_create(thread, NULL, routine, data), code);
    else if (JOIN == code)
        thread_perror(pthread_join(*thread, NULL), code);
    else if (DETACH == code)
        thread_perror(pthread_detach(*thread), code);
    else
        error_exit("Wrong opcode for thread_handle: use <CREATE> <JOIN> <DETACH>");
}

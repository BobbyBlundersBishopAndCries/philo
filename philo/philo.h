/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:58:08 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/09 13:32:45 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdbool.h>
# include <errno.h>
#include "libft/libft.h"
# define RESET "\033[0m"
# define BOLD_RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
typedef enum s_code
{
	CREATE,
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	JOIN,
	DETACH,
}		t_code;

typedef pthread_mutex_t t_mtx;

typedef struct s_philo
{
	pthread_t	thread_id;
	int				id;
	t_mtx	*left_fork;
	t_mtx	*right_fork;
	long			last_meal_time;
	int				eat_count;
	t_data	*data;
}	t_philo;

typedef struct s_fork
{
	t_mtx	mutex;
	int		fork_id;
}	t_fork;

typedef struct s_data
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_fork			*forks;
	t_philo			*philosophers;
	int				start_simulation;
	bool			end_simulation;
}	t_data; 

/* utils.c */
void	error_exit(const char *message);
void	*safe_malloc(size_t size);
/* parsing.c */
void	parse_arguments(char **av, t_data *data);
/* initialization.c */
void	initialize_data(t_data *data, int ac, char **av);
/* thread_handle.c */
void	safe_mutex(t_mtx *mutex, t_code code);
void safe_thread(pthread_t *thread, void *( *routine)(void *),
    void *data, t_code code);

#endif
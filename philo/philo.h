#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct s_philo;

typedef struct s_box
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				full_philos;
	int				death_flag;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	struct s_philo	*philos;
}	t_box;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
   pthread_t		thread;
   t_box			*box;
   int				done_eating;
}	t_philo;

// utils.c
long	get_time(void);
void	msleep(long ms);
void	print_state(t_philo *philo, char *msg, int death_check);
int		is_dead(t_box *box);

// init.c
int		init_box(t_box *box, int ac, char **av);
int		start_threads(t_box *box);
void	cleanup(t_box *box);

void	*take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	put_forks(t_philo *philo);
void	*philo_routine(void *arg);

// monitor.c
void	*monitor(void *arg);

#endif

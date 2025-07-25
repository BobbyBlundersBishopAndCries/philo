#include "philo.h"

void *monitor(void *arg)
{
	t_box *box = (t_box *)arg;
	int i;

	while (!box->death_flag)
	{
		// Check for death first
		i = -1;
		while (++i < box->num_philos)
		{
			pthread_mutex_lock(&box->death_lock);
			long last_meal = box->philos[i].last_meal;
			pthread_mutex_unlock(&box->death_lock);
			if (get_time() - last_meal > box->time_to_die)
			{
				pthread_mutex_lock(&box->death_lock);
				box->death_flag = 1;
				print_state(&box->philos[i], "died", 1);
				pthread_mutex_unlock(&box->death_lock);
				return (NULL);
			}
			usleep(1000);
		}
		// Then check if all are full
		if (box->must_eat != -1)
		{
			pthread_mutex_lock(&box->death_lock);
			if (box->full_philos >= box->num_philos)
			{
				pthread_mutex_unlock(&box->death_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&box->death_lock);
		}
	}
	return (NULL);
}

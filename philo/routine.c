#include "philo.h"

void *take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork", 0);
	}
	return (NULL);
}

void eat(t_philo *philo)
{
	print_state(philo, "is eating", 0);
	pthread_mutex_lock(&philo->box->death_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->box->death_lock);
	philo->meals++;
	msleep(philo->box->time_to_eat);
	if (philo->box->must_eat != -1 && philo->meals == philo->box->must_eat && !philo->done_eating)
	{
		pthread_mutex_lock(&philo->box->death_lock);
		philo->box->full_philos++;
		philo->done_eating = 1;
		pthread_mutex_unlock(&philo->box->death_lock);
	}
}

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		// Handle single philosopher case
		if (philo->box->num_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_state(philo, "has taken a fork", 0);
			// Wait until death or all full
			while (!is_dead(philo->box))
			{
				pthread_mutex_lock(&philo->box->death_lock);
				int all_full = (philo->box->must_eat != -1 && philo->box->full_philos >= philo->box->num_philos);
				pthread_mutex_unlock(&philo->box->death_lock);
				if (all_full)
					break;
				usleep(1000);
			}
			pthread_mutex_unlock(philo->left_fork);
			break;
		}
		pthread_mutex_lock(&philo->box->death_lock);
		int all_full = (philo->box->must_eat != -1 && philo->box->full_philos >= philo->box->num_philos);
		pthread_mutex_unlock(&philo->box->death_lock);
		if (is_dead(philo->box) || all_full)
			break;
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		print_state(philo, "is sleeping", 0);
		msleep(philo->box->time_to_sleep);
		print_state(philo, "is thinking", 0);
	}
	return (NULL);
}

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(long ms)
{
	long start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

void	print_state(t_philo *philo, char *msg, int death_check)
{
	pthread_mutex_lock(&philo->box->print_lock);
	long now = get_time();
	long ts = now - philo->box->start_time;
	if (ts < 0) ts = 0;
	int id = philo->id > 0 ? philo->id : 1;
	if (!philo->box->death_flag || death_check)
		printf("%ld %d %s\n", ts, id, msg);
	pthread_mutex_unlock(&philo->box->print_lock);
}

int	is_dead(t_box *box)
{
	int	ret;
	pthread_mutex_lock(&box->death_lock);
	ret = box->death_flag;
	pthread_mutex_unlock(&box->death_lock);
	return (ret);
}

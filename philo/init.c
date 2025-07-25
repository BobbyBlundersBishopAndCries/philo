#include "philo.h"

static int	ft_atoi(const char *str)
{
long n = 0;
while (*str == ' ' || (*str >= 9 && *str <= 13))
	str++;
if (*str == '-')
	return (-1); // negative not allowed
if (*str == '+')
	str++;
while (*str >= '0' && *str <= '9') {
	if (n > 2147483647)
		return (-1); // overflow
	n = n * 10 + (*str++ - '0');
}
if (n > 2147483647)
	return (-1); // overflow
return (n);
}

int	init_box(t_box *box, int ac, char **av)
{
	int i;

	box->num_philos = ft_atoi(av[1]);
	box->time_to_die = ft_atoi(av[2]);
	box->time_to_eat = ft_atoi(av[3]);
	box->time_to_sleep = ft_atoi(av[4]);
	box->must_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
	if (box->num_philos <= 0 || box->time_to_die <= 0 || box->time_to_eat <= 0 || box->time_to_sleep <= 0 || (ac == 6 && box->must_eat <= 0))
		return (0);
	box->death_flag = 0;
	box->full_philos = 0;
	box->forks = malloc(sizeof(pthread_mutex_t) * box->num_philos);
	box->philos = malloc(sizeof(t_philo) * box->num_philos);
	if (!box->forks || !box->philos)
		return (0);
	pthread_mutex_init(&box->print_lock, NULL);
	pthread_mutex_init(&box->death_lock, NULL);
	i = -1;
	while (++i < box->num_philos)
		pthread_mutex_init(&box->forks[i], NULL);
	i = -1;
	while (++i < box->num_philos)
		box->philos[i].done_eating = 0; // Initialize done_eating
	return (1);
}

int	start_threads(t_box *box)
{
	int i;
	pthread_t mon;

	box->start_time = get_time();
	i = -1;
	while (++i < box->num_philos)
	{
		box->philos[i].id = i + 1;
		box->philos[i].meals = 0;
		box->philos[i].last_meal = box->start_time;
		box->philos[i].left_fork = &box->forks[i];
		box->philos[i].right_fork = &box->forks[(i + 1) % box->num_philos];
		box->philos[i].box = box;
		pthread_create(&box->philos[i].thread, NULL, philo_routine, &box->philos[i]);
	}
	pthread_create(&mon, NULL, monitor, box);
	pthread_join(mon, NULL);
	i = -1;
	while (++i < box->num_philos)
		pthread_join(box->philos[i].thread, NULL);
	return (1);
}

void cleanup(t_box *box)
{
	for (int i = 0; i < box->num_philos; i++)
		pthread_mutex_destroy(&box->forks[i]);
	pthread_mutex_destroy(&box->print_lock);
	pthread_mutex_destroy(&box->death_lock);
	free(box->forks);
	free(box->philos);
}

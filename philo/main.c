#include "philo.h"

int	main(int ac, char **av)
{
	t_box	box;

	if (ac != 5 && ac != 6)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (!init_box(&box, ac, av))
	{
		printf("Error: Invalid arguments (must be positive integers, no overflow, no negative)\n");
		return (1);
	}
	if (!start_threads(&box))
		return (1);
	cleanup(&box);
	return (0);
}

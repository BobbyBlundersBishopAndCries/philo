/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:05:15 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/09 17:48:03 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_init(t_data *data)
{
	
}

void	initialize_data(t_data *data)
{
	int	i;

	i = 0;
	data->forks = safe_malloc(sizeof(t_fork) * data->n_philos);
	data->n_philos = safe_malloc(sizeof(t_philo) * data->n_philos);
	data->end_simulation = false;
	while (i++ < data->n_philos)
	{
		safe_mutex(&data->forks[i].mutex, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
}
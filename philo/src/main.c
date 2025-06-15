/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:42:40 by mohabid           #+#    #+#             */
/*   Updated: 2025/05/30 11:44:31 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int main(int argc, char **argv)
{
	if (argc == 5)
	{
		
	}
	else
	{
		error_exit("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>");
	}	
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:42:02 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/07 16:05:34 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

static const char	*valid_args(const char *s)
{
	int len;
	const char *start;
	
	while (ft_isspace(*s))
		s++;
	len = 0;
	if (*s == '+')
		s++;
	if (*s == '-')
		error_exit("Invalid argument: Negative numbers are not allowed.");
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			error_exit("Invalid argument: Only digits are allowed.");
		s++;
	}
	start = s;
	while (ft_isdigit(*s++))
		len++;
	if (len > 10)
		error_exit("Invalid argument: Number is too large.");
	return (start);
}

void	parse_arguments(char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(valid_args(av[1]));
	data->time_to_die = ft_atoi(valid_args(av[2])) * 1000;
	data->time_to_eat = ft_atoi(valid_args(av[3])) * 1000;
	data->time_to_sleep = ft_atoi(valid_args(av[4])) * 1000;
	if (data->time_to_die <= 6e4 || data->time_to_eat <= 6e4 || data->time_to_sleep <= 6e4)
		error_exit("Invalid argument: Time values must be greater than 60 ms.");
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:00:58 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/08 19:00:59 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_exit(const char *message)
{
	ft_printf(2, BOLD_RED "Error: %s\n" RESET, message);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("Memory allocation failed");
	return (ptr);
}


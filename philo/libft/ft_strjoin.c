/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:42:02 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/30 11:28:24 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	k;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (i + 1));
	if (!joined)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		joined[k + i] = s2[k];
		k++;
	}
	joined[k + i] = '\0';
	return (joined);
}
/*
int main()
{
	const char *s1 = "Hello ";
	const char *s2 = "wol0d";
	char *joined = ft_strjoin(s1,s2);
	if(joined)
	{
		printf("The concatenated strings are %s\n",joined);
		free(joined);
	}
	else
		printf("Memory allocation failure.\n");
	return 0;
}*/

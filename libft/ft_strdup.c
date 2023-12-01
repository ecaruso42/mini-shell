/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:03:17 by duzegbu           #+#    #+#             */
/*   Updated: 2023/01/19 16:03:59 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*destination;
	char	*t;

	i = 0;
	t = ((destination = (char *)malloc(ft_strlen(src) * sizeof(char) + 1)));
	if (!t)
	{
		return (0);
	}
	while (src[i])
	{
		destination[i] = src[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}

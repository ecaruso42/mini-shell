/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:41:24 by duzegbu           #+#    #+#             */
/*   Updated: 2023/01/26 16:57:05 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*dst;
	char	*source;
	size_t	dslen;
	size_t	rest;

	dst = dest;
	source = (char *) src;
	rest = size;
	while (rest-- != 0 && *dst != '\0')
		dst++;
	dslen = dst - dest;
	rest = size - dslen;
	if (rest == 0)
		return (dslen + ft_strlen((char *) src));
	while (*src != '\0')
	{
		if (rest > 1)
		{
			*dst++ = *src;
			rest--;
		}
		src++;
	}
	*dst = '\0';
	return (dslen + (src - source));
}

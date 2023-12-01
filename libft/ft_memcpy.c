/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:11:38 by duzegbu           #+#    #+#             */
/*   Updated: 2023/01/16 13:19:36 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	char	*dst;
	char	*sr;

	i = 0;
	dst = dest;
	sr = (void *) src;
	while (n-- > 0 && dest != src)
	{
		dst[i] = sr[i];
		i++;
	}
	return (dest);
}

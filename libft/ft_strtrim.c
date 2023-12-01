/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:30:56 by duzegbu           #+#    #+#             */
/*   Updated: 2023/01/26 20:08:05 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		end;
	int		start;

	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	if (!set)
		return (ft_strdup(s1));
	while (check(s1[start], set) && s1[start])
		start++;
	while (end > start && check(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	str = ft_memcpy(str, (s1 + start), end - start);
	str[end - start] = 0;
	return (str);
}

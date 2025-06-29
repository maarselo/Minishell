/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 03:41:03 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/13 03:41:03 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_inset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_inset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_inset(s1[end - 1], set))
		end--;
	len = end - start;
	s2 = (char *)malloc(len + 1);
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1 + start, len);
	s2[len] = '\0';
	return (s2);
}

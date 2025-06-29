/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:21:13 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/04 20:21:13 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	j = 0;
	while (big[j] && j < len)
	{
		i = 0;
		while (big[i + j] == little[i] && little[i] && (i + j) < len)
			i++;
		if (little[i] == '\0')
			return ((char *)(big + j));
		j++;
	}
	return (NULL);
}

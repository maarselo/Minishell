/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:43:11 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/12 15:43:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add(unsigned char *d, const unsigned char *s, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		i--;
		d[i] = s[i];
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src && n > 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (s < d && s + n > d)
		ft_add(d, s, n);
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

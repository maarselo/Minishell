/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:55:14 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/05 14:55:14 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			i;
	unsigned char	*cptr;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	cptr = (unsigned char *)ptr;
	while (i < nmemb * size)
	{
		cptr[i] = 0;
		i++;
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:13:34 by mvillavi          #+#    #+#             */
/*   Updated: 2024/12/30 21:13:35 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t numBytes)
{
	unsigned char	*dest;
	unsigned char	*src;

	dest = (unsigned char *)to;
	src = (unsigned char *)from;
	while (numBytes--)
		*dest++ = *src++;
	return (to);
}

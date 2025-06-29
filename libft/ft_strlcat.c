/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:28:40 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/11 16:16:58 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta funcion a diferencia de strncat, que concatena el numero de caracteres
pasas el size de buffer dest, una manera de que siempre se ponga el nulo, y el
y el valor de retorno es la suma de caracteres, de ambas str.*/

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (dstsize <= len_dest)
		return (dstsize + len_src);
	i = len_dest;
	while (i < dstsize - 1 && *src)
		dest[i++] = *src++;
	dest[i] = '\0';
	return (len_dest + len_src);
}

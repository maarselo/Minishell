/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:27:26 by mvillavi          #+#    #+#             */
/*   Updated: 2024/12/24 21:22:35 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Memset, rellena un bloque de memoria con un valor especifico; recibe un 
puntero, int a ASCII, y cantidad de bytes a recorrer, con el valor de int, 
a partir de la direcion asignara el valor a cada BYTE de esa memoria hasta el 
numero de bytes a llenar.*/

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n --)
		*p++ = c;
	return (ptr);
}

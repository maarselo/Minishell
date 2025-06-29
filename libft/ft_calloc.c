/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:13:21 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/12 20:18:56 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (size == 0 || nmemb == 0)
		return (malloc(1));
	if (size != 0 && nmemb > INT_MAX / size)
		return (NULL);
	ptr = (char *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	while (i < nmemb)
		ptr[i++] = '\0';
	return (ptr);
}

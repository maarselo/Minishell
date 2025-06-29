/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:27:16 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/05 18:18:40 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	while (*big && len > 0)
	{
		if (*little == *big && len >= len_little \
				&& ft_strncmp(big, little, len_little) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

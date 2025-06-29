/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:59:09 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/05 13:59:11 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	i;

	ptr = ft_strdup(s);
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		ptr[i] = f(i, s[i]);
	return (ptr);
}

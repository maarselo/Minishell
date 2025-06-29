/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 00:27:18 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/17 10:57:03 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		ptr[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		ptr[s1_len + i] = s2[i];
	ptr[s1_len + s2_len] = '\0';
	return (ptr);
}

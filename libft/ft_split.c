/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:31:40 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/07 17:03:30 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_countw(char *s, int c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static	size_t	ft_lenw(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static	char	**ft_free(int n, char **array)
{
	while (n >= 0)
		free(array[n--]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	w_len;
	size_t	words;

	if (s == NULL)
		return (NULL);
	words = ft_countw((char *)s, c);
	ptr = (char **)malloc((words + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (words--)
	{
		while (*s == c && *s)
			s++;
		w_len = ft_lenw((char *)s, c);
		ptr[i] = ft_substr((char *)s, 0, w_len);
		if (ptr[i] == NULL)
			return (ft_free(i, ptr));
		s += w_len;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

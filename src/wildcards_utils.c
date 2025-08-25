/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:05:06 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/25 19:24:31 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_empty_matches(char	*str)
{
	char	**matches;

	matches = malloc(sizeof(char *) * 2);
	if (!matches)
		return (NULL);
	matches[0] = ft_strdup(str);
	matches[1] = NULL;
	return (matches);
}

int	ft_array_len(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_free_cmd(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

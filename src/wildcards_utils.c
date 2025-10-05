/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:05:06 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 21:07:18 by fbanzo-s         ###   ########.fr       */
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
	if (!matches[0])
		return (NULL);
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

char	**ft_loop_entries(DIR *dir, char *pattern, char **matches,
			char *dir_name)
{
	struct dirent	*entry;
	int				i;
	char			*full_path;

	i = ft_array_len(matches);
	entry = readdir(dir);
	while (entry)
	{
		if (ft_ignore_file(entry, pattern) == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		if (ft_match(pattern, entry->d_name))
		{
			full_path = ft_strjoin(dir_name, entry->d_name);
			matches = ft_realloc_array(matches, i + 1);
			if (!full_path || !matches)
				return (NULL);
			matches[i++] = full_path;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

int	ft_ignore_file(struct dirent *entry, char *pattern)
{
	if (ft_strcmp(entry->d_name, ".") == 0
		|| ft_strcmp(entry->d_name, "..") == 0
		|| (entry->d_name[0] == '.' && pattern[0] != '.'))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:10:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/27 00:01:53 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_match(char *cmd, char *str)
{
	int	cmd_i;
	int	str_i;
	int	cmd_pattern_i;
	int	str_backup_i;

	cmd_pattern_i = -1;
	str_backup_i = -1;
	cmd_i = 0;
	str_i = 0;
	while (str[str_i])
	{
		if (cmd[cmd_i] == '*')
		{
			cmd_pattern_i = cmd_i;
			str_backup_i = str_i;
			cmd_i++;
		}
		else if (cmd[cmd_i] == str[str_i])
		{
			cmd_i++;
			str_i++;
		}
		else if (cmd_pattern_i != -1)
		{
			cmd_i = cmd_pattern_i + 1;
			str_i = str_backup_i + 1;
			str_backup_i++;
		}
		else
			return (0);
	}
	while (cmd[cmd_i] == '*')
		cmd_i++;
	return (cmd[cmd_i] == '\0');
}

char	**ft_realloc_array(char **array, int size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	if (array)
	{
		while (array[i])
		{
			new[i] = array[i];
			i++;
		}
		free(array);
	}
	new[size] = NULL;
	return (new);
}

char	**ft_expand_wildcard(char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				i;

	matches = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (ft_empty_matches(str));
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && str)
		if (ft_match(str, entry->d_name))
		{
			matches = ft_realloc_array(matches, i + 1);
			matches[i] = ft_strdup(entry->d_name);
			i++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (i == 0)
		return (ft_empty_matches(str));
	matches = ft_realloc_array(matches, i + 1);
	if (!matches)
		return (NULL);
	matches[i] = NULL;
	return (matches);
}

char	**ft_join_wildcards(char **cmd, int index, char **wc_expanded)
{
	char	**new_cmd;
	int		j;
	int		i;
	int		k;
	int		wc_len;

	wc_len = ft_array_len(wc_expanded);
	new_cmd = malloc(sizeof(char *) * (wc_len + ft_array_len(cmd)));
	if (!new_cmd)
		return (NULL);
	i = 0;
	k = 0;
	while (i < index)
	{
		new_cmd[k] = ft_strdup(cmd[i]);
		i++;
		k++;
	}
	j = 0;
	while (j < wc_len)
	{
		new_cmd[k] = ft_strdup(wc_expanded[j]);
		j++;
		k++;
	}
	i++;
	while (cmd[i])
	{
		new_cmd[k] = ft_strdup(cmd[i]);
		i++;
		k++;
	}
	new_cmd[k] = NULL;
	return (new_cmd);
}

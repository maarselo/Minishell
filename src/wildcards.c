/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:10:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/03 00:54:41 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new_cmd[k++] = ft_strdup(cmd[i++]);
	j = 0;
	while (j < wc_len)
		new_cmd[k++] = ft_strdup(wc_expanded[j++]);
	i++;
	while (cmd[i])
		new_cmd[k++] = ft_strdup(cmd[i++]);
	new_cmd[k] = NULL;
	return (new_cmd);
}

int	ft_match(char *cmd, char *str)
{
	t_match	m;

	m.cmd_pattern_i = -1;
	m.str_backup_i = -1;
	m.cmd_i = 0;
	m.str_i = 0;
	while (str[m.str_i])
	{
		if (cmd[m.cmd_i] == '*')
			ft_handle_asterisk(&m);
		else if (cmd[m.cmd_i] == str[m.str_i])
		{
			m.cmd_i++;
			m.str_i++;
		}
		else if (m.cmd_pattern_i != -1)
			ft_handle_backtrack(&m);
		else
			return (0);
	}
	while (cmd[m.cmd_i] == '*')
		m.cmd_i++;
	return (cmd[m.cmd_i] == '\0');
}

char	**ft_expand_wildcard(char *pattern)
{
	DIR				*dir;
	char			**matches;
	int				i;
	char			*dir_name;
	char			*name_pattern;

	matches = NULL;
	ft_split_dir(pattern, &dir_name, &name_pattern);
	dir = opendir(dir_name);
	if (dir == NULL)
	{
		free(dir_name);
		free(name_pattern);
		return (ft_empty_matches(pattern));
	}
	matches = ft_loop_entries(dir, name_pattern, matches, dir_name);
	free(dir_name);
	free(name_pattern);
	i = ft_array_len(matches);
	if (i == 0 || matches == NULL)
		return (ft_empty_matches(pattern));
	matches = ft_realloc_array(matches, i + 1);
	matches[i] = NULL;
	return (matches);
}

void	ft_execute_wildcards(t_data *data, t_command *cmd, int *i)
{
	char	**wc_expanded;
	char	**temp_cmd;

	(void)data;
	wc_expanded = ft_expand_wildcard(cmd->command[*i]);
	if (!wc_expanded)
		ft_free_data_exit(data, T_GENERAL_ERROR);
	temp_cmd = cmd->command;
	cmd->command = ft_join_wildcards(temp_cmd, *i, wc_expanded);
	if (!cmd->command)
		ft_free_data_exit(data, T_GENERAL_ERROR);
	ft_free_cmd(temp_cmd);
	*i += ft_array_len(wc_expanded);
	ft_free_cmd(wc_expanded);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:10:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 21:26:06 by fbanzo-s         ###   ########.fr       */
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
	int	cmd_i;
	int	str_i;
	int	cmd_pt_i;
	int	str_bck_i;

	cmd_pt_i = -1;
	str_bck_i = -1;
	cmd_i = 0;
	str_i = 0;
	while (str[str_i])
	{
		if (cmd[cmd_i] == '*')
			ft_match_case1(&cmd_pt_i, &str_bck_i, &cmd_i, &str_i);
		else if (cmd[cmd_i] == str[str_i])
			ft_match_case2(&cmd_i, &str_i);
		else if (cmd_pt_i != -1)
			ft_match_case3(&cmd_pt_i, &str_bck_i, &cmd_i, &str_i);
		else
			return (0);
	}
	while (cmd[cmd_i] == '*')
		cmd_i++;
	return (cmd[cmd_i] == '\0');
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
	if (!dir_name) 
		return (NULL);
	dir = opendir(dir_name);
	if (dir == NULL)
		return (free(name_pattern), free(dir_name), ft_empty_matches(pattern));
	matches = ft_loop_entries(dir, name_pattern, matches, dir_name);
	free(dir_name);
	free(name_pattern);
	if (matches == NULL)
		return (NULL);
	i = ft_array_len(matches);
	if (i == 0 || matches == NULL)
		return (ft_empty_matches(pattern));
	matches = ft_realloc_array(matches, i + 1);
	if (!matches)
		return (NULL);
	return (matches);
}

void	ft_execute_wildcards(t_data *data, t_command *cmd, int *i)
{
	char	**wc_expanded;
	char	**temp_cmd;

	wc_expanded = ft_expand_wildcard(cmd->command[*i]);
	if (!wc_expanded)
		ft_exit_free_data(data, T_GENERAL_ERROR);
	temp_cmd = cmd->command;
	cmd->command = ft_join_wildcards(temp_cmd, *i, wc_expanded);
	if (!cmd->command)
		ft_exit_free_data(data, T_GENERAL_ERROR);
	ft_free_cmd(temp_cmd);
	*i += ft_array_len(wc_expanded);
	ft_free_cmd(wc_expanded);
}

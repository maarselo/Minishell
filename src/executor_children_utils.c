/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_children_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 20:06:37 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_check_if_is_absolute_path(char *command, char **env_array,
				t_data *data)
{
	char	*path;

	if (access(command, X_OK) == 0)
	{
		path = ft_strdup(command);
		if (!path)
			return (ft_error_malloc_free_envarray_data(env_array, data));
		return (path);
	}
	return (NULL);
}

static char	*ft_search_in_path(char *command, char **split_path,
				char **env_array, t_data *data)
{
	int		i;
	char	*tmp;
	char	*path;

	i = -1;
	while (split_path[++i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		if (!tmp)
			return (ft_error_malloc_free_envarray_data(env_array, data));
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (!path)
			return (ft_error_malloc_free_envarray_data(env_array, data));
		if (access(path, X_OK) == 0)
			return (ft_free_split(split_path), path);
		free(path);
	}
	return (ft_free_split(split_path), NULL);
}

char	*ft_find_path(t_command *current, char **env_array, t_data *data)
{
	char	*tmp;
	char	*path;
	char	**split_path;

	path = ft_check_if_is_absolute_path(current->command[0], env_array, data);
	if (path)
		return (path);
	tmp = ft_get_env_value(data->env, "PATH");
	if (!tmp)
		return (NULL);
	split_path = ft_split(tmp, ':');
	free(tmp);
	if (!split_path)
		return (ft_error_malloc_free_envarray_data(env_array, data));
	return (ft_search_in_path(current->command[0],
			split_path, env_array, data));
}

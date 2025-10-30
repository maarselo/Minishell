/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_env_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 20:06:37 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_env_size(t_env *env_list)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static char	*ft_create_array_value(char *mode, t_env *current, char **env_array, t_data *data)
{
	char	*str;
	char	*prev_to_free;

	str = NULL;
	if (!ft_strcmp(WITH_VALUE, mode))
	{
		str = ft_strjoin(current->name, "=");
		if (!str)
			return (ft_error_malloc_free_envarray_data(env_array, data));
		prev_to_free = str;
		str = ft_strjoin(str, current->value);
		free(prev_to_free);
		if (!str)
			return (ft_error_malloc_free_envarray_data(env_array, data));
	}
	else if (!ft_strcmp(NULL_VALUE, mode))
	{
		str = ft_strjoin(current->name, "=");
		if (!str)
			return (ft_error_malloc_free_envarray_data(env_array, data));
	}
	return (str);
}

char	**ft_convert_list(t_data *data)
{
	int		i;
	int		size;
	char	**env_array;
	t_env	*current_env_node;

	i = 0;
	current_env_node = data->env;
	size = ft_get_env_size(data->env);
	env_array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!env_array)
		return (perror("minishell"), ft_free_data_exit(data, T_GENERAL_ERROR), NULL);
	while (current_env_node)
	{
		if (current_env_node->name && current_env_node->value)
			env_array[i] = ft_create_array_value(WITH_VALUE, current_env_node, env_array, data);
		else if (current_env_node->name)
			env_array[i] = ft_create_array_value(NULL_VALUE, current_env_node, env_array, data);
		current_env_node = current_env_node->next;
		i++;
	}
	return (env_array);
}

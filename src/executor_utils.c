/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 20:06:37 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_get_previous_command(t_command *find, t_command *command_list)
{
	t_command	*tmp;
	t_command	*previous;

	if (find == command_list)
		return (NULL);
	previous = command_list;
	tmp = command_list->next;
	while (tmp)
	{
		if (tmp == find)
			return (previous);
		previous = tmp;
		tmp = tmp->next;
	}
	return (tmp);
}

bool	ft_is_last_command(t_command *command)
{
	t_command	*tmp;

	tmp = command;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp == command)
		return (true);
	return (false);
}

int	ft_get_env_size(t_env *env_list)
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

char	*ft_create_array_value(int i, char *mode, t_env *current)
{
	char	*str;
	char	*prev_to_free;

	if (!ft_strcmp(WITH_VALUE, mode))
	{
		str = ft_strjoin(current->name, "=");
		if (!str)
			return (NULL);
		prev_to_free = str;
		str = ft_strjoin(str, current->value);
		free(prev_to_free);
		if (!str)
			return (NULL);
	}
	else if (!ft_strcmp(NULL_VALUE, mode))
	{
		str = ft_strjoin(current->name, "=");
		if (!str)
			return (NULL);
	}
	return (str);
}

char	**ft_convert_list(t_env *env_list)
{
	int		i;
	int		size;
	char	**env_array;
	t_env	*tmp;

	i = 0;
	tmp = env_list;
	size = ft_get_env_size(env_list);
	env_array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	while (tmp)
	{
		if (tmp->name && tmp->value)
			ft_create_array_value(i, WITH_VALUE, tmp);
		else if (tmp->name)
			ft_create_array_value(i, NULL_VALUE, tmp);
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

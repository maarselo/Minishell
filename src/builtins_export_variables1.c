/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_variables1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:19:54 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/04 23:06:35 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_all_asnum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '\"' && !ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

static void	ft_replace_env_var(t_data *data, char *name_var, char *new_value)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strcmp(current->name, name_var) == 0)
		{
			free(current->value);
			current->value = new_value;
			return ;
		}
		current = current->next;
	}
}

static t_env	*ft_create_node_export_by_mode(char *mode, char *var_name,
			char *var_value, t_data *data)
{
	t_env	*node_env;

	node_env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node_env)
		return (free(var_name), free(var_value),
			ft_perror_free_data_exit(data, T_GENERAL_ERROR), NULL);
	node_env->name = var_name;
	if (!ft_strcmp(mode, NO_VALUE))
		ft_set_global_exit_status(T_SUCCESS);
	else if (!ft_strcmp(mode, NULL_VALUE) || !ft_strcmp(mode, WITH_VALUE))
	{
		node_env->value = var_value;
		ft_set_global_exit_status(T_SUCCESS);
	}
	return (node_env);
}

static void	ft_add_var_into_list(t_env *env, t_env *env_list)
{
	t_env	*tmp;

	if (!env_list)
	{
		env_list = env;
		return ;
	}
	tmp = env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = env;
}

void	ft_create_and_add_variable(char *mode, char *command, t_data *data)
{
	t_env	*env;
	char	*var_name;
	char	*var_value;

	var_name = ft_split_name_var(command, data);
	var_value = ft_split_value_var(command, data, var_name);
	if (ft_find_env_var_name(data->env, var_name) == 0)
	{
		ft_replace_env_var(data, var_name, var_value);
		free(var_name);
	}
	else
	{
		env = ft_create_node_export_by_mode(mode, var_name, var_value, data);
		ft_add_var_into_list(env, data->env);
	}
}

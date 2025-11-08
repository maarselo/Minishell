/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_variables1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:19:54 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 16:17:23 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_shlvl(char *mode, char *var_name, char *new_value,
			t_data *data)
{
	char	*tmp;
	int		number;
	char	*str_number;
	t_env	*env_node;

	if (ft_strcmp("SHLVL", var_name))
		return (0);
	number = ft_atoi(new_value);
	free(new_value);
	if (number > 1000)
	{
		ft_printf_fd(2, "minishell: shell level to high, resetting to 1\n");
		number = 1;
	}
	else if (number < 0)
		number = 0;
	env_node = data->env;
	while (env_node)
	{
		if (!ft_strcmp(env_node->name, "SHLVL"))
		{
			if (!ft_strcmp(mode, MODE_WRITE))
			{
				free(env_node->value);
				env_node->value = ft_itoa(number);
			}
			else if (!ft_strcmp(mode, MODE_APPEND))
			{
				tmp = env_node->value;
				str_number = ft_itoa(number);
				env_node->value = ft_strjoin(env_node->value, str_number);
				free(tmp);
				free(str_number);
				if (ft_atoi(env_node->value) > 1000)
				{
					free(env_node->value);
					env_node->value = ft_strdup("1");
					ft_printf_fd(2, "minishell: shell level to high, resetting to 1 ");
				}
			}
		}
		env_node = env_node->next;
	}
	return (1);
}

static int	ft_replace_env_var(char *mode, t_data *data, char *var_name,
		char *new_value)
{
	t_env	*current;
	char	*tmp;

	current = data->env;
	while (current)
	{
		if (ft_check_shlvl(mode, var_name, new_value, data))
			return (1);
		if (ft_strcmp(current->name, var_name) == 0)
		{
			if (ft_strcmp(mode, MODE_APPEND) == 0)
			{
				tmp = current->value;
				current->value = ft_strjoin(current->value, new_value);
				return (free(tmp), free(new_value), 1);
			}
			else if (ft_strcmp(mode, MODE_WRITE) == 0)
			{
				free(current->value);
				current->value = new_value;
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
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
		ft_set_global_exit_status(data, T_SUCCESS);
	else if (!ft_strcmp(mode, NULL_VALUE) || !ft_strcmp(mode, WITH_VALUE))
	{
		node_env->value = var_value;
		ft_set_global_exit_status(data, T_SUCCESS);
	}
	return (node_env);
}

static void	ft_add_var_into_list(t_env *env, t_env **env_list)
{
	t_env	*tmp;

	if (!*env_list)
	{
		*env_list = env;
		return ;
	}
	tmp = *env_list;
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
	var_value = NULL;
	if (ft_strcmp(mode, NO_VALUE))
		var_value = ft_split_value_var(command, data, var_name);
	if (ft_find_env_var_name(data->env, var_name) == 0)
	{
		if (command[ft_strlen_var_name(command) - 1] == '+')
			ft_replace_env_var(MODE_APPEND, data, var_name, var_value);
		else
			ft_replace_env_var(MODE_WRITE, data, var_name, var_value);
		free(var_name);
	}
	else
	{
		env = ft_create_node_export_by_mode(mode, var_name, var_value, data);
		ft_add_var_into_list(env, &data->env);
	}
}

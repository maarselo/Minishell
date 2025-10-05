/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:22:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 17:59:08 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_order_variables(t_env *list)
{
	t_env	*order_env;
	t_env	*tmp;

	order_env = ft_clone_env_list(list);
	if (!order_env)
		return ;
	tmp = order_env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\'%s\'\n", tmp->name, tmp->value);
		else
			printf("declare -x %s=\'\'\n", tmp->name);
		tmp = tmp->next;
	}
}

void	ft_add_var_into_list(t_env *env, t_env *env_list)
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

int	ft_create_and_add_variable(char *mode, char *command, t_env *env_list)
{
	t_env	*env;
	char	*name_var;
	char	*new_value;

	name_var = ft_split_name_var(command);
	new_value = ft_split_value_var(command);
	if (ft_find_env_var_name(env_list, name_var) == 0)
	{
		ft_replace_env_var(env_list, name_var, new_value);
		free(name_var);
		free(new_value);
		return (0);
	}
	env = ft_create_node_export_by_mode(mode, command);
	ft_add_var_into_list(env, env_list);
	free(name_var);
	free(new_value);
	return (0);
}

int	ft_export_single(char *cmd, t_env *env_list)
{
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || ft_contains_metachar(cmd))
	{
		printf("minishell: export: `%s`: not a valid identifier\n", cmd);
		ft_set_global_exit_status(T_GENERAL_ERROR);
		return (1);
	}
	if (!ft_strchr(cmd, '=') && ft_is_all_asnum(cmd))
		return (ft_create_and_add_variable(NO_VALUE, cmd, env_list));
	if (ft_strchr(cmd, '=') && cmd[ft_strlen(cmd) - 1] == '=')
		return (ft_create_and_add_variable(NULL_VALUE, cmd, env_list));
	if (ft_strchr(cmd, '=') && cmd[ft_strlen(cmd) - 1] != '=')
		return (ft_create_and_add_variable(WITH_VALUE, cmd, env_list));
	return (0);
}

void	ft_export(char **command, t_env *env_list)
{
	int		i;

	i = 1;
	if (!command[1])
	{
		ft_print_order_variables(env_list);
		ft_set_global_exit_status(T_SUCCESS);
		return ;
	}
	while (command[i])
	{
		if (ft_export_single(command[i], env_list))
			continue ;
		ft_set_global_exit_status(T_SUCCESS);
		i++;
	}
}

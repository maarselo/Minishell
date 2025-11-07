/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:22:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 16:17:58 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_order_variables(t_data *data)
{
	t_env	*order_env;
	t_env	*tmp;

	order_env = ft_clone_env_list(data);
	if (!order_env)
		return ;
	tmp = order_env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\'%s\'\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	ft_free_envp(order_env);
}

static int	ft_export_single(char *cmd, t_data *data)
{
	if (ft_isdigit(cmd[0]) || cmd[0] == '='
		|| ft_contains_metachar_var_name(cmd))
	{
		printf("minishell: export: `%s`: not a valid identifier\n", cmd);
		ft_set_global_exit_status(data, T_GENERAL_ERROR);
		return (1);
	}
	else if (!ft_strchr(cmd, '=') && ft_is_all_asnum(cmd))
		ft_create_and_add_variable(NO_VALUE, cmd, data);
	else if (ft_strchr(cmd, '=') && cmd[ft_strlen(cmd) - 1] == '=')
		ft_create_and_add_variable(NULL_VALUE, cmd, data);
	else if (ft_strchr(cmd, '=') && cmd[ft_strlen(cmd) - 1] != '=')
		ft_create_and_add_variable(WITH_VALUE, cmd, data);
	return (0);
}

void	ft_export(char **command, t_data *data)
{
	int		i;

	i = 1;
	if (!command[1])
	{
		ft_print_order_variables(data);
		ft_set_global_exit_status(data, T_SUCCESS);
		return ;
	}
	while (command[i])
	{
		if (ft_export_single(command[i], data))
		{
			i++;
			ft_set_global_exit_status(data, T_GENERAL_ERROR);
			continue ;
		}
		ft_set_global_exit_status(data, T_SUCCESS);
		i++;
	}
}

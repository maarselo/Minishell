/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:46:23 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 18:15:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	ft_execute_builtin(bool is_last, t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->command[0], "echo") == 0)
		ft_echo(data, cmd->command);
	else if (ft_strcmp(cmd->command[0], "cd") == 0)
		ft_cd(cmd->command, data);
	else if (ft_strcmp(cmd->command[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		ft_unset(data, cmd->command, &data->env);
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		ft_env(cmd->command, data);
	else if (ft_strcmp(cmd->command[0], "export") == 0)
		ft_export(cmd->command, data);
	else if (ft_strcmp(cmd->command[0], "exit") == 0)
		ft_exit_handler(cmd, data);
	if (cmd->connector == AND_CONNECTOR
		|| cmd->connector == OR_CONNECTOR || is_last)
		return (ft_check_wheter_continue(cmd, data));
	return (1);
}

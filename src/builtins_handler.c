/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:46:23 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 20:35:55 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ft_isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "echo") )
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
	return (0);
}

int	ft_execute_builtin(t_command *cmd, t_env **env_list, t_command *list)
{
	(void)list;
	if (ft_strcmp(cmd->command[0], "echo") == 0)
		ft_echo(cmd->command);
	else if (ft_strcmp(cmd->command[0], "cd") == 0)
		ft_cd(cmd->command, *env_list);
	else if (ft_strcmp(cmd->command[0], "pwd") == 0)
		ft_pwd(cmd->command);
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		ft_unset(cmd->command, env_list);
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		ft_env(cmd->command, *env_list);
	else if (ft_strcmp(cmd->command[0], "export") == 0)
		ft_export(cmd, *env_list);
	if (g_status.exit_status != T_SUCCESS)
		return (0);
	return (1);
}
*/
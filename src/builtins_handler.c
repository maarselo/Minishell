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

int	ft_isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
//mange arguemts errors
void	ft_execute_builtin(t_command *cmd, t_env **env_list, t_command *list)
{
	if (ft_strcmp(cmd->command[0], "echo") == 0)
		ft_echo(cmd->command);
	if (ft_strcmp(cmd->command[0], "cd") == 0)
		ft_cd(cmd->command, *env_list);
	if (ft_strcmp(cmd->command[0], "pwd") == 0)
		ft_pwd(cmd->command);
	if (ft_strcmp(cmd->command[0], "unset") == 0)
		ft_unset(cmd->command, env_list);
	if (ft_strcmp(cmd->command[0], "env") == 0)
		ft_env(cmd->command, *env_list);
	if (ft_strcmp(cmd->command[0], "export") == 0)
		ft_export(cmd->command, *env_list);
}

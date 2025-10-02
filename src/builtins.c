/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:46:23 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 04:13:07 by fbanzo-s         ###   ########.fr       */
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

void	ft_execute_builtin(t_command *cmd, t_env **env_list)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmd->command);
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(cmd->command, *env_list);
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(cmd->command);
	if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(cmd->command, env_list);
}

void	ft_echo(char **args)
{
	bool	flag_n;
	int		i;

	i = 0;
	flag_n = false;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		flag_n = true;
		i++;
	}
	while (args[i] && ft_strcmp(args[i], "-n"))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_status.exit_status = 0;
}

void	ft_pwd(char **args)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(cwd);
		g_status.exit_status = 0;
	}
	else
	{
		perror("minishell: pwd");
		g_status.exit_status = 1;
	}
}

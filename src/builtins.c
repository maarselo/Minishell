/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:46:23 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/09/11 20:38:03 by fbanzo-s         ###   ########.fr       */
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

void	ft_execute_builtin(t_command *cmd, t_env *env_list)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmd->command);
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(cmd->command, env_list);
}

void	ft_cd(char **args, t_env *env_list)
{
	char	**path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_status.exit_status = 1;
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		g_status.exit_status = 1;
	}
	else
	{
		ft_update_pwd(path);
        g_status.exit_status = 0;
	}
}

void	ft_echo(char **args)
{
	bool	flag_n;
	int		i;

	i = 0;
	flag_n = false;
	if (args[1] && ft_strcmp(args[1], "-n"))
	{
		flag_n = true;
		i++;
	}
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

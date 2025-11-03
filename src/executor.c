/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/10/06 21:31:35 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_child(t_command *current_cmd, t_data *data)
{
	char	*path;
	char	**env_array;

	env_array = ft_convert_list(data);
	path = ft_find_path(current_cmd, env_array, data);
	if (!path)
		ft_error_command_not_found(current_cmd, env_array, data);
	if (execve(path, current_cmd->command, env_array) == -1)
		ft_error_command_not_found(current_cmd, env_array, data);
}

static void	ft_update_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ft_set_global_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_set_global_exit_status(128 + WTERMSIG(status));
}

int	ft_check_wheter_continue(t_command *command)
{
	if (command->connector == AND_CONNECTOR && g_status.exit_status != 0)
		return (0);
	else if (command->connector == OR_CONNECTOR && g_status.exit_status == 0)
		return (0);
	return (1);
}

int	ft_execute_command(bool is_last, t_command *current_command, t_data *data)
{
	pid_t	pid;

	if (ft_isbuiltin(current_command->command[0]))
		return (ft_execute_builtin(is_last, current_command, data));
	pid = fork();
	if (pid == -1)
		return (perror("minishell:"),
			ft_set_global_exit_status(T_GENERAL_ERROR), 0);
	else if (pid == 0)
	{
		ft_set_signals_child_mode();
		ft_execute_child(current_command, data);
	}
	else
	{
		if (current_command->connector == AND_CONNECTOR
			|| current_command->connector == OR_CONNECTOR || is_last)
		{
			ft_update_exit_status(pid);
			return (ft_check_wheter_continue(current_command));
		}
	}
	return (1);
}

void	ft_executor(t_data *data)
{
	int			prev_pipe;
	int			keep;
	t_command	*current_command;

	prev_pipe = -1;
	current_command = data->cmd;
	while (current_command)
	{
		if (ft_manage_pipes(&prev_pipe, current_command, data->cmd)
			|| ft_check_heredoc(current_command, &prev_pipe))
			return ;
		if (ft_manage_redirections(current_command))
			ft_close_pipe(&prev_pipe);
		else if (current_command->command)
		{
			if (current_command->next)
				keep = ft_execute_command(false, current_command, data);
			else
				keep = ft_execute_command(true, current_command, data);
		}
		ft_resturare_defaults_fd(data);
		if (!keep)
			break ;
		current_command = current_command->next;
	}
}

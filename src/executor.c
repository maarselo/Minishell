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

static char	*ft_find_path(t_command *current, t_env *env_list)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**split_path;

	i = -1;
	if (access(current->command[0], X_OK) == 0)
		return (ft_strdup(current->command[0]));
	tmp = ft_get_env_value(env_list, "PATH");
	if (!tmp)
		return (printf("minishell: command not found\n"),
			exit(T_COMMAND_NOT_FOUND), NULL);
	split_path = ft_split(tmp, ':');
	if (!split_path)
		return (free(tmp), perror("minishell :"), exit(T_GENERAL_ERROR), NULL);
	free(tmp);
	while (split_path[++i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(tmp, current->command[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (ft_free_split(split_path), path);
		free(path);
	}
	return (ft_free_split(split_path), NULL);
}

void	ft_execute_child(t_command *current_cmd, t_data *data)
{
	char	*path;
	char	**env_array;

	env_array = ft_convert_list(data->env);
	if (!env_array)
	{
		perror("minishell: ");
		ft_free_data_exit(data, T_GENERAL_ERROR);
		exit(T_GENERAL_ERROR);
	}
	path = ft_find_path(current_cmd, data->env);
	if (!path)
	{
		printf("Command %s not found \n", current_cmd->command[0]);
		ft_free_data_exit(data, T_COMMAND_NOT_FOUND);
	}
	if (execve(path, current_cmd->command, env_array) == -1)
	{
		printf("Command %s not found \n", current_cmd->command[0]);
		ft_free_data_exit(data, T_COMMAND_NOT_FOUND);
	}
}

int	ft_execute_command(bool is_last, t_command *current_command, t_data *data)
{
	pid_t	pid;
	int		status;

	if (ft_isbuiltin(current_command->command[0]))
		return (ft_execute_builtin(is_last, current_command, data));
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), 0);
	else if (pid == 0)
	{
		ft_set_signals_child_mode();
		ft_execute_child(current_command, data);
	}
	else
	{
		if (current_command->connector == AND_CONNECTOR
			|| current_command->connector == OR_CONNECTOR
			|| is_last)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				ft_set_global_exit_status(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				ft_set_global_exit_status(128 + WTERMSIG(status));
			if (g_status.exit_status != 0
				&& current_command->connector == AND_CONNECTOR)
				return (0);
			else if (g_status.exit_status == 0
				&& current_command->connector == OR_CONNECTOR)
				return (0);
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
		else
		{
			if (current_command->next)
				keep = ft_execute_command(false, current_command, data);
			else
				keep = ft_execute_command(true, current_command, data);
		}
		ft_resturare_defaults_fd(data->saved_fd);
		if (!keep)
			break ;
		current_command = current_command->next;
	}
}

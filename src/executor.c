/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_env_size(t_env *env_list)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_list;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_convert_list(t_env *env_list)
{
	int		i;
	int		size;
	char	**env_array;
	char	*prev_to_free;
	t_env	*tmp;

	i = 0;
	tmp = env_list;
	size = ft_get_env_size(env_list);
	env_array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!env_array)
		return (NULL); 
	while (tmp)
	{
		if (tmp->name && tmp->value)
		{
			env_array[i] = ft_strjoin(tmp->name,"=");
			if (!env_array[i])
                return (NULL);
			prev_to_free = env_array[i];
			env_array[i] = ft_strjoin(env_array[i], tmp->value);
			free(prev_to_free);
			if (!env_array[i])
				return (NULL);
		}
		else if (tmp->name)
		{
			env_array[i] = ft_strjoin(tmp->name, "=");
            if (!env_array[i])
                return (NULL); 
		}
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

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

void	ft_execute_child(t_command *current_cmd, t_env *env, t_command *list)
{
	char	*path;
	char	**env_array;

	env_array = ft_convert_list(env);
	if (!env_array)
	{
		perror("minishell: ");
		ft_free_data(env, list);
		exit(T_GENERAL_ERROR);
	}
	path = ft_find_path(current_cmd, env);
	if (!path)
	{
		ft_free_data(env, list);
		printf("Command %s not found \n", current_cmd->command[0]);
		exit(T_COMMAND_NOT_FOUND);
	}
	if (execve(path, current_cmd->command, env_array) == -1)
	{
		printf("Command %s not found \n", current_cmd->command[0]);
		ft_free_data(env, list);
		exit(T_COMMAND_NOT_FOUND);
	}
}

int	ft_execute_command(t_command *current_command, t_env **env_list, t_command *command_list, bool is_last)
{
	pid_t	pid;
	int		status;

	if (ft_isbuiltin(current_command->command[0]))
		ft_execute_builtin(current_command, env_list, command_list);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), 0);
	else if (pid == 0)
	{
		//ft_set_signals_child_mode()
		ft_execute_child(current_command, *env_list, command_list);
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
			if (g_status.exit_status != 0 && current_command->connector == AND_CONNECTOR)
				return (0);
			else if (g_status.exit_status == 0 && current_command->connector == OR_CONNECTOR)
				return (0);
		}
	}
	return (1);
}

void	ft_executor(t_command *command_list, t_saved_fd saved_fd, t_env **env)
{
	int			prev_pipe;
	int			keep;
	t_command	*current_command;

	prev_pipe = -1;
	current_command = command_list;
	while (current_command)
	{
		if (ft_manage_pipes(&prev_pipe, current_command, command_list)
			|| ft_manage_redirections(current_command))
			return ;
		if (current_command->next) 
			keep = ft_execute_command(current_command, env, command_list, false);
		else
			keep = ft_execute_command(current_command, env, command_list, true);
		ft_resturare_defaults_fd(saved_fd);
		if (!keep)
			break ;
		current_command = current_command->next;
	}
}

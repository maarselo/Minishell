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
/*
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

char	*ft_get_env_value_by_name(char *name, t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
	}
	return (NULL);
}

char	*ft_find_path(char *command, t_env *env_list)
{
	char	*value;
	char	**paths;
	char	*tmp;
	char	*possible_path;
	int		i;

	i = -1;
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK));
			return (ft_strdup(command));
	}
	value = ft_get_env_value_by_name("PATH", env_list);
	if (!value)
		return (NULL);
	paths = ft_split(value, ':');
	if (!paths)
		return (perror("minishell :"), NULL);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		possible_path = ft_strjoin(tmp, command);
		free (tmp);
		if (!access(possible_path, X_OK))
			return (ft_free_split(paths), possible_path);
		free(possible_path);
	}
	return (ft_free_split(paths), NULL);
}

int	ft_execute_command(t_command *current_command, t_env *env_list)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**env_array;

	if (ft_is_builtin(current_command->command[0]))
	{
		ft_execute_builtin(current_command->command, env_list);
		//dont know how interprete
		//return
	}
	env_array = ft_convert_list(env_list);//to free
	pid = fork();
	if (pid == -1)
		return (perror("minishell: "), 1);
	if (pid == 0)
	{
		path = ft_find_path(current_command->command[0], env_list);
		if (!path)
			return (ft_free_argv_command(env_array), ft_putstr_fd("minishell: command not found:" , STDERR_FILENO), printf(" %s", current_command), ft_set_global_exit_status(T_COMMAND_NOT_FOUND), 1);
		if (execve(path, current_command->command, env_array) == -1)
			return (ft_free_argv_command(env_array), ft_putstr_fd("minishell: command not found:" , STDERR_FILENO), printf(" %s", current_command), ft_set_global_exit_status(T_COMMAND_NOT_FOUND), 1);
	}
	else
	{
		if (current_command->connector = AND)
	}
}

void	ft_executor(t_command *command_list, t_saved_fd saved_fd, t_env *env)
{
	(void)env;
	int			prev_pipe;
	t_command	*current_command;

	prev_pipe = -1;
	current_command = command_list;
	while (current_command)
	{
		if (ft_manage_pipes(&prev_pipe, current_command, command_list)
			|| ft_manage_redirections(current_command))
			return ;//IDK if i need to kill all process
		//ft_execute_command(current_command, env);
		ft_resturare_defaults_fd(saved_fd);
		current_command = current_command->next;
	}
}
*/
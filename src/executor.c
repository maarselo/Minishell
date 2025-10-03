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
/*
int	ft_execute_command(t_command *current_command, t_env *env_list)
{

}*/

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

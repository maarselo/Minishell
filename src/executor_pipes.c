/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:57:46 by mvillavi          #+#    #+#             */
/*   Updated: 2025/10/02 20:16:05 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe(int *prev_pipe)
{
	if (*prev_pipe != -1)
	{
		close(*prev_pipe);
		*prev_pipe = -1;
	}
}

int	ft_manage_pipes(int *prev_pipe, t_command *current_command,
			t_command *command_list)
{
	int			pipe_fd[2];
	t_command	*previous;

	previous = ft_get_previous_command(current_command, command_list);
	if (*prev_pipe != -1 && previous && previous->connector == PIPE_CONNECTOR)
		dup2(*prev_pipe, STDIN_FILENO);
	if (current_command->connector == PIPE_CONNECTOR)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_error_creating_pipe(prev_pipe), 1);
		if (*prev_pipe != -1)
			close(*prev_pipe);
		*prev_pipe = dup(pipe_fd[0]);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	return (0);
}

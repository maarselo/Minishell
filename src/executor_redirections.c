/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_manage_pipes(int *prev_pipe, t_command *current_command,
			t_command *command_list)
{
	int			pipe_fd[2];
	t_command	*previous;

	previous = ft_get_previous_command(current_command, command_list);
	if (*prev_pipe != 1 && previous && previous->connector == PIPE_CONNECTOR)
		dup2(*prev_pipe, STDIN_FILENO);
	if (current_command->connector == PIPE_CONNECTOR)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_error_creating_pipe(prev_pipe), 1);
		*prev_pipe = pipe_fd[0];
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	return (0);
}

/*señalesssssssw
void	ft_heredoc(char *delimiter, int *pipefd)
{

}*/

static int	ft_open_redirection_file(char *mode, t_command *command)
{
	int	fd;

	fd = 0;
	if (!ft_strncmp(mode, MODE_READ, ft_strlen(mode)))
		fd = open(command->redirection->infile, O_RDONLY, 0644);
	else if (!ft_strncmp(mode, MODE_WRITE, ft_strlen(mode)))
		fd = open(command->redirection->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (!ft_strncmp(mode, MODE_APPEND, ft_strlen(mode)))
		fd = open(command->redirection->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (0);
	return (fd);
}

int	ft_manage_redirections(t_command *current_command)
{
	int	fd;

	if (current_command->redirection->infile)
	{
		fd = ft_open_redirection_file(MODE_READ, current_command);
		if (fd == -1)
			return (ft_error_opening_files(), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (current_command->redirection->outfile)
	{
		if (current_command->redirection->append)
			fd = ft_open_redirection_file(MODE_APPEND, current_command);
		else
			fd = ft_open_redirection_file(MODE_WRITE, current_command);
		if (fd == -1)
			return (ft_error_opening_files(), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

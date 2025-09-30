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
	if (*prev_pipe != -1 && previous && previous->connector == PIPE_CONNECTOR)
		dup2(*prev_pipe, STDIN_FILENO);
	if (current_command->connector == PIPE_CONNECTOR)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_error_creating_pipe(prev_pipe), 1);
		if (*prev_pipe != -1 )
			close(*prev_pipe);
		*prev_pipe = dup(pipe_fd[0]);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	return (0);
}

//señalesssssssw
static int	ft_heredoc(char *delimiter)
{
	char	*content;
	int		pipe_fd[2];
	
	ft_set_signals_heredoc_mode();
	if (pipe(pipe_fd) == -1)
		return (ft_error_creating_pipe(NULL), 1);
	write(1, "> ", 2);
	content = get_next_line(0);
	while (content)
	{
		if (g_status.heredoc_status == 1)
			return (ft_set_global_heredoc_status(0), 1);
		if (!ft_strncmp(delimiter, content, ft_strlen(content) - 1))
		{
			free(content);
			break;
		}
		write(pipe_fd[1], content, ft_strlen(content));
		free(content);
		write(1, "> ", 2);
		content = get_next_line(0);
	}
	if (!content)
	{
		ft_set_global_exit_status(T_SUCCESS);//indicate the EOF
		printf("minishell: here-document delimited by end-of-file (wanted %s)\n", delimiter);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}

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
		return (-1);
	return (fd);
}

int	ft_manage_redirections(t_command *current_command)
{
	int	fd;

	if (current_command->redirection)
	{
		if (current_command->redirection->infile)
		{
			fd = ft_open_redirection_file(MODE_READ, current_command);
			if (fd == -1)
				return (ft_error_opening_files(), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (current_command->redirection->heredoc)
		{
			if (ft_heredoc(current_command->redirection->delimiter))
				return (1);
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
	}
	return (0);
}

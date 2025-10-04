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

static int	ft_heredoc(char *delim)
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
		if (!ft_strncmp(delim, content, ft_strlen(content) - 1))
			return (free(content), dup2(pipe_fd[0], STDIN_FILENO),
				close(pipe_fd[0]), close(pipe_fd[1]), 0);
		write(pipe_fd[1], content, ft_strlen(content));
		free(content);
		write(1, "> ", 2);
		content = get_next_line(0);
	}
	ft_set_global_exit_status(T_SUCCESS);
	printf("minishell: here-doc delimited by EOF (wanted %s)\n", delim);
	return (dup2(pipe_fd[0], STDIN_FILENO), close(pipe_fd[0]),
		close(pipe_fd[1]), 0);
}

static int	ft_open_redirection_file(char *mode, t_command *command)
{
	int	fd;

	fd = 0;
	if (!ft_strncmp(mode, MODE_READ, ft_strlen(mode)))
		fd = open(command->redirection->infile, O_RDONLY, 0644);
	else if (!ft_strncmp(mode, MODE_WRITE, ft_strlen(mode)))
		fd = open(command->redirection->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (!ft_strncmp(mode, MODE_APPEND, ft_strlen(mode)))
		fd = open(command->redirection->outfile,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

static int	ft_manage_outfile_redir(t_command *current_command)
{
	int	fd;

	if (current_command->redirection->append)
		fd = ft_open_redirection_file(MODE_APPEND, current_command);
	else
		fd = ft_open_redirection_file(MODE_WRITE, current_command);
	if (fd == -1)
		return (ft_error_opening_files(), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
			if (ft_manage_outfile_redir(current_command))
				return (1);
		}
	}
	return (0);
}

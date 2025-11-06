/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/06 20:19:27 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc(t_command *command, t_data *data)
{
	char	*content;
	int		pipe_fd[2];

	//ft_set_signals_heredoc_mode();
	if (pipe(pipe_fd) == -1)
		return (ft_error_creating_pipe(data, NULL), 1);
	write(data->saved_fd.saved_stdout, "> ", 2);
	content = get_next_line(data->saved_fd.saved_stdin);
	while (content)
	{
		if (data->heredoc_status == 1)
			return (ft_heredoc_sigint_handler(content, pipe_fd, data));
		if (!ft_strncmp_heredoc(command->redirection->delimiter, content,
				ft_strlen(command->redirection->delimiter))
			&& content[ft_strlen(command->redirection->delimiter)] == '\n')
			return (free(content), ft_dup_close_pipe_heredoc(pipe_fd));
		write(pipe_fd[1], content, ft_strlen(content));
		free(content);
		write(data->saved_fd.saved_stdout, "> ", 2);
		content = get_next_line(data->saved_fd.saved_stdin);
	}
	ft_set_global_exit_status(data, T_SUCCESS);
	printf("minishell: here-doc delimited by EOF (wanted %s)\n",
		command->redirection->delimiter);
	return (ft_dup_close_pipe_heredoc(pipe_fd));
}

static int	ft_open_redirection_file(char *mode,
			t_command *command, t_data *data)
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
		return (ft_error_opening_files(data), 1);
	if (!ft_strncmp(mode, MODE_READ, ft_strlen(mode)))
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), 1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), 1);
	}
	close(fd);
	return (0);
}

int	ft_check_heredoc(t_command *current_command, int *prev_pipe, t_data *data)
{
	if (current_command->redirection)
	{
		if (current_command->redirection->heredoc)
		{
			if (ft_heredoc(current_command, data))
			{
				ft_close_pipe(prev_pipe);
				return (1);
			}
		}
	}
	return (0);
}

int	ft_manage_redirections(t_command *current_command, t_data *data)
{
	if (current_command->redirection)
	{
		if (current_command->redirection->infile)
		{
			if (ft_open_redirection_file(MODE_READ, current_command, data))
				return (1);
		}
		if (current_command->redirection->outfile)
		{
			if (current_command->redirection->append)
			{
				if (ft_open_redirection_file(MODE_APPEND,
						current_command, data))
					return (1);
			}
			else
			{
				if (ft_open_redirection_file(MODE_WRITE, current_command, data))
					return (1);
			}
		}
	}
	return (0);
}

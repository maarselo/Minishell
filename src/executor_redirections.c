/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/07 02:42:55 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc(t_command *command, t_data *data)
{
	char	*content;
	int		pipe_fd[2];

	ft_set_signals_heredoc_mode();
	if (pipe(pipe_fd) == -1)
		return (ft_error_creating_pipe(data, NULL), 1);
	while (1)
	{
		if (g_signal != 0)
			break ;
		write(data->saved_fd.saved_stdout, "> ", 2);
		content = get_next_line(data->saved_fd.saved_stdin);
		if (!content)
			break ;
		if (!ft_strncmp_heredoc(command->redirection->delimiter, content,
				ft_strlen(command->redirection->delimiter))
			&& content[ft_strlen(command->redirection->delimiter)] == '\n')
			return (free(content), ft_dup_close_pipe_heredoc(pipe_fd));
		write(pipe_fd[1], content, ft_strlen(content));
		free(content);
	}
	return (ft_check_heredoc_signal(data, command, pipe_fd));
}

int	ft_check_heredoc(t_command *command, int *prev_pipe, t_data *data)
{
	char	*delim;

	if (command->redirection)
	{
		if (command->redirection->heredoc)
		{
			if (ft_strchr(command->redirection->delimiter, '\'')
				|| ft_strchr(command->redirection->delimiter, '\"'))
			{
				delim = command->redirection->delimiter;
				command->redirection->delimiter = ft_remove_quotes(delim);
			}
			if (ft_heredoc(command, data))
			{
				ft_close_pipe(prev_pipe);
				return (1);
			}
		}
	}
	return (0);
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
		return (ft_error_opening_files(mode, command, data), 1);
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

int	ft_manage_redirections(t_command *command, t_data *data)
{
	if (command->redirection)
	{
		if (command->redirection->infile)
		{
			ft_check_have_quotes(INFILE, data);
			if (ft_open_redirection_file(MODE_READ, command, data))
				return (1);
		}
		if (command->redirection->outfile)
		{
			ft_check_have_quotes(OUTFILE, data);
			if (command->redirection->append)
			{
				if (ft_open_redirection_file(MODE_APPEND, command, data))
					return (1);
			}
			else
				if (ft_open_redirection_file(MODE_WRITE, command, data))
					return (1);
		}
	}
	return (0);
}

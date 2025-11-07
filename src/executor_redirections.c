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
	char	*delim;

	if (current_command->redirection)
	{
		if (current_command->redirection->heredoc)
		{
			if (ft_strchr(current_command->redirection->delimiter, '\'')
				|| ft_strchr(current_command->redirection->delimiter, '\"'))
			{
				delim = current_command->redirection->delimiter;
				current_command->redirection->delimiter
					= ft_remove_quotes(delim);
			}
			if (ft_heredoc(current_command, data))
			{
				ft_close_pipe(prev_pipe);
				return (1);
			}
		}
	}
	return (0);
}

int	ft_manage_redirections(t_command *curr_cmd, t_data *data)
{
	if (curr_cmd->redirection)
	{
		if (curr_cmd->redirection->infile)
		{
			if (ft_strchr(curr_cmd->redirection->infile, '\'')
				|| ft_strchr(curr_cmd->redirection->infile, '\"'))
				curr_cmd->redirection->infile = ft_remove_quotes(curr_cmd->redirection->infile);
			if (ft_open_redirection_file(MODE_READ, curr_cmd, data))
				return (1);
		}
		if (curr_cmd->redirection->outfile)
		{
			if (ft_strchr(curr_cmd->redirection->outfile, '\'')
				|| ft_strchr(curr_cmd->redirection->outfile, '\"'))
				curr_cmd->redirection->outfile = ft_remove_quotes(curr_cmd->redirection->outfile);
			if (curr_cmd->redirection->append)
			{
				if (ft_open_redirection_file(MODE_APPEND,
						curr_cmd, data))
					return (1);
			}
			else
			{
				if (ft_open_redirection_file(MODE_WRITE, curr_cmd, data))
					return (1);
			}
		}
	}
	return (0);
}

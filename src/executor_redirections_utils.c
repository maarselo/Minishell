/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/07 00:46:45 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc_sigint_handler(char *content, int pipe_fd[], t_data *data)
{
	ft_set_global_heredoc_status(data, 0);
	ft_set_global_exit_status(data, T_SIGINT);
	free(content);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

int	ft_strncmp_heredoc(const char *delim, const char *line, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && delim[i] && line[i]
		&& (unsigned char)delim[i] == (unsigned char)line[i])
		i++;
	if (i < n)
		return ((unsigned char)delim[i] - (unsigned char)line[i]);
	return (0);
}

int	ft_dup_close_pipe_heredoc(int pipe_fd[])
{
	return (dup2(pipe_fd[0], STDIN_FILENO),
		close(pipe_fd[0]), close(pipe_fd[1]), 0);
}

int	ft_check_heredoc_signal(t_data *data,
			t_command *command, int *pipe_fd)
{
	if (g_signal != 0)
	{
		ft_set_global_exit_status(data, T_SIGINT);
		g_signal = 0;
		return (1);
	}
	ft_set_global_exit_status(data, T_SUCCESS);
	printf("minishell: here-doc delimited by EOF (wanted %s)\n",
		command->redirection->delimiter);
	return (ft_dup_close_pipe_heredoc(pipe_fd));
}

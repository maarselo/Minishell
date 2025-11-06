/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/06 18:11:38 by fbanzo-s         ###   ########.fr       */
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

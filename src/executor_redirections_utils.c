/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc_sigint_handler(char *content, int pipe_fd[])
{
	ft_set_global_heredoc_status(0);
	ft_set_global_exit_status(T_SIGINT);
	free(content);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

int	ft_strncmp_heredoc(const char *delim, const char *line, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_isalspace((char *)line))
		return (1);
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

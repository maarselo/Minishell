/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//señalesssssssw
void	ft_heredoc(char *delimiter, int *pipefd)
{
	char	*content;

	//if (pipe(fd) == -1)
	//	ft_error_creating_pipe();
	write(1, "> ", 2);
	content = get_next_line(0);
	while (content)
	{
		if (!ft_strncmp(content, delimiter, ft_strlen(delimiter))
			&& content[ft_strlen(delimiter)] == '\n')
		{
			free(content);
			break ;
		}
		write(1, "> ", 2);
		write(pipefd[1], content, ft_strlen(content));
		free(content);
		content = get_next_line(0);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}
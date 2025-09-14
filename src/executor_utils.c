/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 20:06:37 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_get_previous_command(t_command *find, t_command *command_list)
{
	t_command	*tmp;
	t_command	*previous;

	if (find == command_list)
		return (NULL);
	previous = command_list;
	tmp = command_list->next;
	while (tmp)
	{
		if (tmp == find)
			return (previous);
		previous = tmp;
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_manage_redirection(int *pipefd[2], t_command *current_command, t_command *command_list)
{
	int			fd;
	t_command	*previous;

	previous = ft_get_previous_command(current_command, command_list);
	// para el primer comando
	if (!previous)
	{
		//if (previous->connector == PIPE_CONNECTOR)
		//	dup2(pipefd[0], STDIN_FILENO);
		if (current_command->redirection->infile)
		{
			fd = open(current_command->redirection->infile, O_RDONLY, 0644);
			if (fd == -1)
			{	
				printf("minishell: Permission denied.");
				ft_set_global_exit_status(T_FILE_PERMITS);
				return ;
			}
			dup2(fd, STDIN_FILENO);
		}
		else if (current_command->redirection->heredoc)
		{
			if (pipe(*pipefd) == -1)
				ft_error_creating_pipe(command_list);
			ft_heredoc(current_command->redirection->delimiter, pipefd);
			dup2(pipefd[0], STDIN_FILENO);
		}
		if (current_command->redirection->outfile)
		{
			if (current_command->redirection->append == true)
			{
				fd = open(current_command->redirection->outfile, O_WRONLY, O_CREAT, O_APPEND, 0644);
				if (fd == -1)
				{
					printf("minishell: Permission denied.");
					ft_set_global_exit_status(T_FILE_PERMITS);
					return ;
				}
				dup2(fd, STDOUT_FILENO);
			}
			else
			{
				fd = open(current_command->redirection->outfile, O_WRONLY, O_CREAT, O_TRUNC, 0644);
				if (fd == -1)
				{
					printf("minishell: Permission denied.");
					ft_set_global_exit_status(T_FILE_PERMITS);
					return ;
				}
				dup2(fd, STDOUT_FILENO);
			}
		}

	}

}
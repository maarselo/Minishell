/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/06 18:05:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
///neccesary exit when is not possible dup at the beginning of the minishell
t_saved_fd	ft_store_defaults_fd(t_env *env_list)
{
	t_saved_fd	saved_fd;

	saved_fd.saved_stdin = dup(STDIN_FILENO);
	saved_fd.saved_stdout = dup(STDOUT_FILENO);
	if (saved_fd.saved_stdin == -1 || saved_fd.saved_stdout == -1)
	{
		ft_free_envp(env_list);
		perror("minishell");
		exit(1);
	}
	return (saved_fd);
}

void	ft_close_defaults_fd(t_saved_fd saved_fd)
{
	if (saved_fd.saved_stdin != -1)
		close(saved_fd.saved_stdin);
	if (saved_fd.saved_stdout != -1)
		close(saved_fd.saved_stdout);
}

void	ft_resturare_defaults_fd(t_data *data)
{
	if (data->saved_fd.saved_stdin != -1)
	{
		if (dup2(data->saved_fd.saved_stdin, STDIN_FILENO) == -1)
			ft_free_data_exit(data, T_GENERAL_ERROR);
	}
	if (data->saved_fd.saved_stdout != -1)
	{
		if (dup2(data->saved_fd.saved_stdout, STDOUT_FILENO) == -1)
			ft_free_data_exit(data, T_GENERAL_ERROR);
	}
}

void	ft_duplicate_stderror_stdin(t_data *data)
{
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		ft_free_data_exit(data, T_GENERAL_ERROR);
}

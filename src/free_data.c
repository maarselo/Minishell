/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 20:26:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_data(t_data *data)
{
	if (data->env)
		ft_free_envp(data->env);
	if (data->cmd)
		ft_free_command_list(data->cmd);
	if (data->saved_fd.saved_stdin != -1)
		close(data->saved_fd.saved_stdin);
	if (data->saved_fd.saved_stdout != -1)
		close(data->saved_fd.saved_stdout);
}

void	ft_exit_free_data(t_data *data, int exit_code)
{
	ft_free_data(data);
	exit(exit_code);
}

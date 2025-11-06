/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_init_data(t_env *env_list, t_saved_fd saved_fd)
{
	t_data		*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		ft_free_envp(env_list);
		ft_close_defaults_fd(saved_fd);
		perror("minishell");
		exit(T_GENERAL_ERROR);
	}
	if (env_list)
		data->env = env_list;
	data->saved_fd = saved_fd;
	data->exit_status = 0;
	data->heredoc_status = 0;
	return (data);
}
/*
void	ft_print_data(t_data *data)
{
	t_command	*tmp_cmd;
	int			i;

	if (!data)
		return ;
	if (data->cmd)
	{
		tmp_cmd = data->cmd;
		while (tmp_cmd)
		{
			i = 0;
			ft_putstr_fd("--- Nuevo Comando ---\n", 1);
			while (tmp_cmd->command[i])
			{
				ft_putstr_fd(tmp_cmd->command[i], 1);
				ft_putstr_fd("\n", 1);
				i++;
			}
			tmp_cmd = tmp_cmd->next;
		}
	}
}*/

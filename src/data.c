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
	data->pid_array = NULL;
	return (data);
}

void	ft_init_pid_array(t_data *data)
{
	data->pid_array = malloc(sizeof(pid_t) * ft_get_total_commands(data->cmd));
	if (!data->pid_array)
		ft_perror_free_data_exit(data, T_GENERAL_ERROR);
}

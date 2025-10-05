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

t_data	*ft_init_data(t_command *command, t_env *env_list,
			t_saved_fd saved_fd)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	if (command)
		data->cmd = command;
	if (env_list)
		data->env = env_list;
	data->saved_fd = saved_fd;
	return (data);
}

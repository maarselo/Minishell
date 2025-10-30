/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_creating_pipe(int *prev_pipe)
{
	if (prev_pipe)
	{
		if (*prev_pipe != 1)
			close(*prev_pipe);
	}
	ft_set_global_exit_status(T_GENERAL_ERROR);
	printf("minishell: Error while creating pipes.");
}

void	ft_error_opening_files(void)
{
	ft_set_global_exit_status(T_FILES);
	perror("minishell");
}

void	*ft_error_malloc_free_envarray_data(char **env_array, t_data *data)
{
	perror("minishell");
	ft_free_split(env_array);
	ft_free_data_exit(data, T_GENERAL_ERROR);
	return (NULL);
}

void	ft_error_command_not_found(t_command *current_cmd, char **env_array,
			t_data *data)
{
	ft_duplicate_stderror_stdin(data);
	printf("minishell: command %s not found \n", current_cmd->command[0]);
	ft_free_split(env_array);
	ft_free_data_exit(data, T_COMMAND_NOT_FOUND);
}

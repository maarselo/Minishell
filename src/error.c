/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/06 18:09:23 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_creating_pipe(t_data *data, int *prev_pipe)
{
	if (prev_pipe)
	{
		if (*prev_pipe != 1)
			close(*prev_pipe);
	}
	ft_set_global_exit_status(data, T_GENERAL_ERROR);
	printf("minishell: Error while creating pipes.");
}

void	ft_error_opening_files(t_data *data)
{
	ft_set_global_exit_status(data, T_FILES);
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

void	ft_perror_free_data_exit(t_data *data, int exit_code)
{
	perror("minishell");
	ft_free_data_exit(data, exit_code);
}

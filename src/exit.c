/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 18:16:06 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(char *input, t_data *data)
{
	if (input)
		free(input);
	if (data)
		ft_free_data(data);
	printf("exit\n");
	exit(T_SUCCESS);
}

void	ft_clean_parser_memory_exit(t_command *command,
	t_data *data, t_token *token_list)
{
	if (command)
	{
		if (command->command)
			ft_free_argv_command(command->command);
		if (command->redirection)
			ft_free_redirections_command(command->redirection);
		free(command);
	}
	if (data)
		ft_free_data(data);
	if (token_list)
		ft_free_token(token_list);
	exit(T_GENERAL_ERROR);
}

void	ft_free_data_exit(t_data *data, int exit_code)
{
	ft_free_data(data);
	exit(exit_code);
}

void	ft_exit_handler(t_command *cmd, t_data *data)
{
	int		number;

	if (ft_get_previous_command(cmd, data->cmd) || cmd->next)
		return ;
	printf("exit\n");
	if (ft_strcmp(cmd->command[0], "exit") == 0 && !cmd->command[1])
		ft_free_data_exit(data, T_SUCCESS);
	if (ft_isnumbers(cmd->command[1]) && cmd->command[2])
		ft_exit_many_arguments(data);
	else if (!ft_isnumbers(cmd->command[1]))
		ft_exit_alphas(cmd, data);
	else if (ft_isnumbers(cmd->command[1]) == 1)
	{
		number = ft_atoi(cmd->command[1]);
		ft_free_data(data);
		if (0 <= number && number <= 255)
			exit(number);
		else
			exit(number % 256);
	}
}

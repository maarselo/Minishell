/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c     c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/03 23:06:32 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_handler(char *input)
{
	int		number;
	char	**exit_split;

	if (!ft_strcmp(input, "exit") || !ft_strcmp(input, "exit "))
	{
		free (input);
		exit (T_SUCCESS);
	}
	exit_split = ft_split(input, ' ');
	free(input);
	if (ft_isnumbers(exit_split[1]) && exit_split[2])
	{
		ft_free_split(exit_split);
		ft_set_global_exit_status(T_GENERAL_ERROR);
		ft_putstr_fd("bash: exit: too many arguments\n",STDOUT_FILENO);
		return ;
	}
	else if (ft_isnumbers(exit_split[1]))
	{
		number = ft_atoi(exit_split[1]);
		ft_free_split(exit_split);
		if (0 <= number || number >= 255)
			exit(number);
		else
			exit(number % 256);
	}
	else if (!ft_isnumbers(exit_split[1]))
	{
		ft_set_global_exit_status(T_SYNTAX);
		printf("bash: exit: %s: numeric argument required\n", exit_split[1]);
		ft_free_split(exit_split);
		return ;
	}
}

void	ft_exit_free_input(char *input)
{
	free(input);
	printf("exit\n");
	exit(0);
}

void	ft_clean_parser_memory_exit(t_command *command, t_command *command_list,
	t_token *token_list)
{
	if (command)
		ft_free_command_list(command);
	if (command_list)
		ft_free_command_list(command_list);
	if (token_list)
		ft_free_token_list(token_list);
	exit(EXIT_FAILURE);
}

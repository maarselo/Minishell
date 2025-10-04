/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 19:24:14 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(char *input)
{
	free(input);
	printf("exit\n");
	exit(T_SUCCESS);
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
	exit(T_GENERAL_ERROR);
}

static void	ft_exit_many_arguments(char **exit_split)
{
	ft_free_split(exit_split);
	ft_set_global_exit_status(T_GENERAL_ERROR);
	ft_putstr_fd("bash: exit: too many arguments\n", STDOUT_FILENO);
}

static void	ft_exit_alphas(char **exit_split)
{
	ft_set_global_exit_status(T_SYNTAX);
	printf("bash: exit: %s: numeric argument required\n", exit_split[1]);
	ft_free_split(exit_split);
	return ;
}

void	ft_exit_handler(char *input)
{
	int		number;
	char	**exit_split;

	printf("exit\n");
	if (!ft_strcmp(input, "exit") || !ft_strcmp(input, "exit "))
	{
		free(input);
		exit(T_SUCCESS);
	}
	exit_split = ft_split(input, ' ');
	free(input);
	if (ft_isnumbers(exit_split[1]) && exit_split[2])
		ft_exit_many_arguments(exit_split);
	else if (!ft_isnumbers(exit_split[1]))
		ft_exit_alphas(exit_split);
	else if (ft_isnumbers(exit_split[1]))
	{
		number = ft_atoi(exit_split[1]);
		ft_free_split(exit_split);
		if (0 <= number && number <= 255)
			exit(number);
		else
			exit(number % 256);
	}
}

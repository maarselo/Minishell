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

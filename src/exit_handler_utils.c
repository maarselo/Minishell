/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:57:46 by mvillavi          #+#    #+#             */
/*   Updated: 2025/10/06 20:33:39 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_many_arguments(char **exit_split)
{
	ft_free_split(exit_split);
	ft_set_global_exit_status(T_GENERAL_ERROR);
	ft_putstr_fd("bash: exit: too many arguments\n", STDOUT_FILENO);
}

void	ft_exit_alphas(char **exit_split)
{
	ft_set_global_exit_status(T_SYNTAX);
	printf("bash: exit: %s: numeric argument required\n", exit_split[1]);
	ft_free_split(exit_split);
	return ;
}

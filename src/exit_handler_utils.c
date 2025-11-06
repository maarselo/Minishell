/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:57:46 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/06 18:16:18 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_many_arguments(t_data *data)
{
	ft_set_global_exit_status(data, T_GENERAL_ERROR);
	ft_putstr_fd("bash: exit: too many arguments\n", STDOUT_FILENO);
}

void	ft_exit_alphas(t_command *cmd, t_data *data)
{
	ft_set_global_exit_status(data, T_SYNTAX);
	printf("bash: exit: %s: numeric argument required\n", cmd->command[1]);
	ft_free_data_exit(data, T_SYNTAX);
}

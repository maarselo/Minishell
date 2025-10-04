/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:14:46 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 04:16:54 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **args, t_env *env_list)
{
	t_env	*current;

	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		ft_set_global_exit_status(T_GENERAL_ERROR);
		return ;
	}
	current = env_list;
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		current = current->next;
	}
	ft_set_global_exit_status(T_SUCCESS);
}

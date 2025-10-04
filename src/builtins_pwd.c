/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:23:42 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 20:33:20 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **args)
{
	char	*cwd;

	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		ft_set_global_exit_status(T_GENERAL_ERROR);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(cwd);
		ft_set_global_exit_status(T_SUCCESS);
	}
	else
	{
		perror("minishell: pwd");
		ft_set_global_exit_status(T_GENERAL_ERROR);
	}
}

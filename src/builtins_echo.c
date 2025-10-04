/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 19:24:14 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	bool	flag_n;
	int		i;

	i = 0;
	flag_n = false;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		flag_n = true;
		i++;
	}
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ft_set_global_exit_status(T_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 19:52:45 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid_nflag(char *flag)
{
	int	i;

	if (!flag || flag[0] != '-')
		return (0);
	i = 1;
	if (flag[i] == '\0')
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_data *data, char **args)
{
	bool	flag_n;
	int		i;

	i = 1;
	flag_n = false;
	while (args[i] && ft_is_valid_nflag(args[i]) == 1)
	{
		flag_n = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag_n == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ft_set_global_exit_status(data, T_SUCCESS);
}

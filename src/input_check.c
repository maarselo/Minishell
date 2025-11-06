/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:22:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 17:59:08 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_null_input(char *input, t_data *data)
{
	if (!input)
	{
		clear_history();
		ft_free_exit(input, data);
	}
}

int	ft_check_void_input(char *input)
{
	if (!ft_strlen(input))
		return (free(input), 1);
	return (0);
}

int	ft_check_if_its_exit(char *input)
{
	if (!ft_strcmp(input, "exit") || !ft_strncmp(input, "exit ", 5))
	{
		clear_history();
		return (1);
	}
	return (0);
}

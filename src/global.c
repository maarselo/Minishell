/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:01:55 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/06 16:09:28 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_global_exit_status(t_data *data, int new_exit_code)
{
	data->exit_status = new_exit_code;
}

void	ft_set_global_heredoc_status(t_data *data, int heredoc_status)
{
	data->heredoc_status = heredoc_status;
}

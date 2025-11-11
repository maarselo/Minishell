/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:59:11 by mvillavi          #+#    #+#             */
/*   Updated: 2025/11/11 11:59:13 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_input_terminal_free_data(t_data *data)
{
	ft_putstr_fd("\033[1;34mminishell\033[0m: input is not a terminal\n", 2);
	ft_free_data(data);
	exit(1);
}

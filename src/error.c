/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change to his struct y cerrar fd????
void	ft_error_creating_pipe(int *prev_pipe)
{
	if (*prev_pipe != 1)
		close(*prev_pipe);
	printf("minishell: Error while creating pipes.");
}

void	ft_error_opening_files()
{
	ft_set_global_exit_status(T_FILES);
	perror("minishell");
}
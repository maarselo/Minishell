/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:39:01 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/24 11:58:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// La barra imprime un quit corr dumped
void	ft_set_signals_child_mode(void)
{
	signal(SIGINT, SIG_DFL);   // Ctrl+C mata al hijo
	signal(SIGQUIT, SIG_DFL);  // Ctrl+\ mata al hijo
}

//void	ft_execute_command(current_command)

//no pasar liberrar aca evnp y command list
void	ft_executor(t_command *command_list, t_env *env)
{
	(void)env;
	int			prev_pipe;
	t_command	*current_command;

	prev_pipe = -1;
	current_command = command_list;
	while (current_command)
	{
		if (ft_manage_pipes(&prev_pipe, current_command, command_list)
			|| ft_manage_redirections(current_command))
			return ;//IDK if i need to kill all process
		//ft_execute_command(current_command);
		current_command = current_command->next;
	}
}

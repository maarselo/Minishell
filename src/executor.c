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
/*
void	ft_sigquit_handler_child_mode(int signal)
{
	(void)signal;
	ft_set_global_exit_status(T_SIGQUIT);
	printf("Quit (core dumped)\n");
}

// La barra imprime un quit corr dumped
void	ft_set_signals_child_mode(void)
{
	signal(SIGINT, SIG_DFL);   // Ctrl+C mata al hijo
	signal(SIGQUIT, SIG_DFL);  // Ctrl+\ mata al hijo
}

//I think i need to change env to [][]
void	ft_execute_command(t_command *current_command, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_set_signals_child_mode();
		ft_execute_command(current_command, env);
	}
	else
	{
		if (current_command->connector == AND_CONNECTOR)
		{
			wait3()
		}
	}
}
*/
//no pasar liberrar aca evnp y command list
void	ft_executor(t_command *command_list, t_saved_fd saved_fd, t_env *env)
{
	(void)env;
	int			prev_pipe;
	t_command	*current_command;
	char	*content = (char *)malloc(sizeof(char) * 7);
	prev_pipe = -1;
	current_command = command_list;
	while (current_command)
	{
		if (ft_manage_pipes(&prev_pipe, current_command, command_list)
			|| ft_manage_redirections(current_command))
			return ;//IDK if i need to kill all process
		read(STDIN_FILENO, content, 7);
		printf("contenido->%s", content);
		//ft_execute_command(current_command);
		ft_resturare_defaults_fd(saved_fd);
		current_command = current_command->next;
	}
}

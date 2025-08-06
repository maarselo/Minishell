/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/06 13:52:29 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This two fucntions are used to set the signals the Ctrl+C, start a new line
	at the prompt and actualice the global exit status from the last command to
	130
*/
static void	ft_sigint_handler_prompt_mode(int signal)
{
	(void)signal;
	g_global.exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_set_signal_prompt_mode(void)
{
	signal(SIGINT, ft_sigint_handler_prompt_mode);
	signal(SIGQUIT, SIG_IGN);
}

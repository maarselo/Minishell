/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/11 15:05:01 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_handler_prompt_mode(int signal)
{
	(void)signal;
	ft_set_global_exit_status(T_SIGINT);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_set_signals_prompt_mode(void)
{
	signal(SIGINT, ft_sigint_handler_prompt_mode);
	signal(SIGQUIT, SIG_IGN);
}

static void	ft_sigint_hadler_heredoc_mode(int signal)
{
	(void)signal;
	ft_set_global_exit_status(T_SIGINT);
	ft_set_global_heredoc_status(1);
}

void	ft_set_signals_heredoc_mode(void)
{
	signal(SIGINT, ft_sigint_hadler_heredoc_mode);
	signal(SIGQUIT, SIG_IGN);
}

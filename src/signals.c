/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/07 02:40:45 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signals_prompt_mode(void)
{
	signal(SIGINT, ft_sigint_handler_prompt_mode);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_set_signals_heredoc_mode(void)
{
	signal(SIGINT, ft_sigint_hadler_heredoc_mode);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_set_signals_child_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_set_signals_parent_mode(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

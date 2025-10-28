/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/30 18:55:47 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_syntax1(t_token *token)
{
	if (ft_check_start_end_types(token))
	{
		ft_putstr_fd("minishell: syntax error near operator.\n", 2);
		return (true);
	}
	if (ft_check_quotes(token))
	{
		ft_putstr_fd("minishell: unmatched quotes.\n", 2);
		return (true);
	}
	if (ft_check_parenthesis(token))
	{
		ft_putstr_fd("minishell: unmatched parenthesis.\n", 2);
		return (true);
	}
	if (ft_check_redirects(token))
	{
		ft_putstr_fd("minishell: error word after redirection.\n", 2);
		return (true);
	}
	return (false);
}

bool	ft_syntax2(t_token *token)
{
	if (ft_check_between_operator(token))
	{
		ft_putstr_fd("minishell: invalid operator sequence.\n", 2);
		return (true);
	}
	if (ft_check_open_parenthesis(token))
	{
		ft_putstr_fd("minishell: invalid opening parenthesis.\n", 2);
		return (true);
	}
	if (ft_check_close_parenthesis(token))
	{
		ft_putstr_fd("minishell: invalid closing parenthesis.\n", 2);
		return (true);
	}
	if (ft_check_if_have_parenthesis(token))
	{
		ft_putstr_fd("minishell: parenthesis must be implemented in the future\n", 2);
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/30 18:29:13 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	ft_check_start_end_types(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == 1 || tmp->type == 6 || tmp->type == 7)
		return (1);
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == 1 || tmp->type == 6 || tmp->type == 7)
		return (1);
	return (0);
}

int	ft_check_quotes(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_check_content_quotes(tmp->content))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_parenthesis(t_token *token)
{
	int		paren_count;
	t_token	*tmp;

	paren_count = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == T_PAREN_OPEN)
			paren_count++;
		else if (tmp->type == T_PAREN_CLOSE)
		{
			paren_count--;
			if (paren_count < 0)
				return (1);
		}
		tmp = tmp->next;
	}
	if (paren_count != 0)
		return (1);
	return (0);
}

int	ft_check_redirects(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
			|| tmp->type == T_REDIR_APPEND || tmp->type == T_HEREDOC)
		{
			if (!tmp->next || tmp->next->type != T_WORD)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

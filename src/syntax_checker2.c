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

int	ft_check_between_operator(t_token *token)// | | && && || || ()
{
	t_token	*previous;
	t_token	*tmp;
	
	previous = token;
	tmp = token;
	while(tmp)
	{
		if (tmp->type == T_PIPE || tmp->type == T_AND || tmp->type == T_OR)
		{
			if (previous != tmp)
			{
				if ((previous->type == T_PIPE) || (previous->type == T_AND) 
					|| (previous->type == T_OR) || (previous->type == T_PAREN_OPEN))
					return (1);
			}
			if ((tmp->next->type == T_PIPE) || (tmp->next->type == T_AND) 
				|| (tmp->next->type == T_OR) || (tmp->next->type == T_PAREN_CLOSE))
				return (1);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_open_parenthesis(t_token *token)
{
	t_token	*previous;
	t_token	*tmp;
	
	previous = token;
	tmp = token;
	while(tmp)
	{
		if (tmp->type == T_PAREN_OPEN)
		{
			if (previous != tmp)
			{
				if (previous->type == T_WORD)
					return (1);
			}
			if ((tmp->next->type == T_PIPE) || (tmp->next->type == T_AND) 
				|| (tmp->next->type == T_OR) || (tmp->next->type == T_PAREN_CLOSE))
				return (1);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_close_parenthesis(t_token *token)
{
	t_token	*previous;
	t_token	*tmp;
	
	previous = token;
	tmp = token;
	while(tmp)
	{
		if (tmp->type == T_PAREN_CLOSE)
		{
			if (previous != tmp)
			{
				if ((previous->type == T_PIPE) || (previous->type == T_AND)
					|| (previous->type == T_OR) || (previous->type == T_PAREN_OPEN))
					return (1);
			}
			if ((tmp->next) && ((tmp->next->type == T_WORD) || (tmp->next->type == T_PAREN_OPEN)))
				return (1);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

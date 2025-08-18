/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:07:41 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/17 13:37:21 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_command(t_token *token_list)
{
	int	count;

	count = 1;
	while (token_list)
	{
		if (token_list->type == T_PIPE || token_list->type == T_OR 
			|| token_list->type == T_AND)
			count++;
		token_list = token_list->next;
	}
	return (count);
}

int	ft_check_if_end_command(t_token *token)
{
	if (!token || token->type == T_PIPE || token->type == T_AND 
		|| token->type == T_OR)
		return (1);
	return (0);
}

t_token	*ft_get_previos_token(bool is_first, t_token *start, t_token *to_find)
{
	t_token	*tmp;
	t_token	*previous;
	
	if (is_first == true)
		return (NULL);
	tmp = start;
	previous = start;
	while (tmp)
	{
		if (tmp == to_find)
			return (previous);
		previous = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_get_if_its_redirection_type(t_token *t)
{
	if (!t)
		return (0);
	return (t->type == T_REDIR_IN || t->type == T_REDIR_OUT
		|| t->type == T_REDIR_APPEND || t->type == T_HEREDOC);
}

void	ft_add_command_to_linked_list(t_command *new_command, t_command *top)
{
	t_command	*tmp;

	tmp = top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_command;
}
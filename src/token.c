/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:55:14 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/04 00:36:51 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	ft_get_type_token(char	*content)
{
	if (ft_strncmp(content, "|", 1) == 0)
		return (T_PIPE);
	else if (ft_strncmp(content, ">", 1) == 0)
		return (T_REDIR_OUT);
	else if (ft_strncmp(content, "<", 1) == 0)
		return (T_REDIR_IN);
	else if (ft_strncmp(content, ">>", 1) == 0)
		return (T_REDIR_APPEND);
	else if (ft_strncmp(content, "<<", 1) == 0)
		return (T_HEREDOC);
	else
		return (T_WORD);
}

t_token	*ft_init_token(char	*content)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = content;
	new_token->type = ft_get_type_token(content);
	new_token->next = NULL;
	return (new_token);
}

void	ft_print_tokens(t_token	*token)
{
	t_token	*first_token;

	first_token = token;
	while (first_token)
	{
		ft_printf("%s\n", first_token->content);
		first_token = first_token->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/12 23:47:30 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	ft_get_token_type(char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (T_PIPE);
	else if (!ft_strncmp(token, ">", ft_strlen(token)))
		return (T_REDIR_OUT);
	else if (!ft_strncmp(token, "<", ft_strlen(token)))
		return (T_REDIR_IN);
	else if (!ft_strncmp(token, ">>", ft_strlen(token)))
		return (T_REDIR_APPEND);
	else if (!ft_strncmp(token, "<<", ft_strlen(token)))
		return (T_HEREDOC);
	else if (!ft_strncmp(token, "&&", ft_strlen(token)))
		return (T_AND);
	else if (!ft_strncmp(token, "||", ft_strlen(token)))
		return (T_OR);
	else if (!ft_strncmp(token, "(", ft_strlen(token)))
		return (T_PAREN_OPEN);
	else if (!ft_strncmp(token, ")", ft_strlen(token)))
		return (T_PAREN_CLOSE);
	else
		return (T_WORD);
}

static bool	ft_token_is_quoted(char *content)
{
	int	len;

	if (!content)
		return (false);
	len = ft_strlen(content);
	if (len < 2)
		return (false);
	return ((content[0] == '\'' && content[len - 1] == '\'')
		|| (content[0] == '"' && content[len - 1] == '"'));
}

t_token	*ft_init_token(char *content)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = ft_get_token_type(content);
	token->is_quoted = ft_token_is_quoted(content);
	token->next = NULL;
	return (token);
}

void	ft_free_token(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

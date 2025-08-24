/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:22:57 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/18 14:01:24 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_have_any_redirection(t_token *start, t_token *end)
{
	t_token	*tmp;

	tmp = start;
	while (tmp && tmp != end)
	{
		if (ft_get_if_its_redirection_type(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_set_redirect_infile(int *malloc_error, t_token *token,
		t_redirect *redirections)
{
	if (redirections->infile)
		free(redirections->infile);
	if (redirections->delimiter)
	{
		free(redirections->delimiter);
		redirections->delimiter = NULL;
	}
	redirections->heredoc = false;
	redirections->infile = ft_strdup_with_flag(malloc_error,
			token->next->content);
}

void	ft_set_redirect_heredoc(int *malloc_error, t_token *token,
		t_redirect *redirections)
{
	if (redirections->delimiter)
		free(redirections->delimiter);
	if (redirections->infile)
	{
		free(redirections->infile);
		redirections->infile = NULL;
	}
	redirections->heredoc = true;
	redirections->delimiter = ft_strdup_with_flag(malloc_error,
			token->next->content);
}

void	ft_set_redirect_outfile(int *malloc_error, t_token *token,
		t_redirect *redirections)
{
	if (redirections->outfile)
		free(redirections->outfile);
	redirections->append = false;
	redirections->outfile = ft_strdup_with_flag(malloc_error,
			token->next->content);
}

void	ft_set_redirect_append(int *malloc_error, t_token *token,
		t_redirect *redirections)
{
	if (redirections->outfile)
		free(redirections->outfile);
	redirections->append = true;
	redirections->outfile = ft_strdup_with_flag(malloc_error,
			token->next->content);
}

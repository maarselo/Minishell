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
//show on 2? add returns
/*
bool validate_tokens(t_token *token_list)
{
	while (token)
	{
		// aquí pones todas las reglas una por una
		token = token->next;
	}
}*/
void	*ft_syntax(t_token *token)
{

	if (ft_check_start_end_types(token))
		return (printf("minishell: syntax error near unexpected operator\n"), NULL);
	if (ft_check_quotes(token))
		return (printf("minishell: syntax error unmatched delimiter\n"), NULL);
	if (ft_check_parenthesis(token))
		return (printf("minishell: syntax error unmatched parenthesis.\n"), NULL);
	if (ft_check_redirects(token))
		return (printf("minishell: syntax error expected word after redirection\n"), NULL);
	if (ft_check_between_operator(token))
		return (printf("minishell: syntax error invalid combination or sequence of operators\n"), NULL);
	if (ft_check_open_parenthesis(token))
		return (printf("minishell: syntax error invalid opening parenthesis placement\n"), NULL);
	if (ft_check_close_parenthesis(token))
		return (printf("minishell: syntax error invalid closing parenthesis placement\n"), NULL);
	return (NULL);
}
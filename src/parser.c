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
t_cmd	*ft_parser(t_token *token)
{
	if (ft_check_start_end_types(token))
		return (printf("minishell: syntax error near unexpected operator\n"));
	if (ft_check_delimiters(token))
		return (printf("minishell: syntax error unmatched delimiter\n"));
	if (ft_check_redirects(token))
		return (printf("minishell: syntax error expected word after redirection\n"));
}
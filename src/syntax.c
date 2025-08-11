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

bool	ft_syntax(t_token *token)
{
	if (ft_check_start_end_types(token))
		return (printf("minishell: syntax error near unexpected operator\n"), true);
	if (ft_check_quotes(token))
		return (printf("minishell: syntax error unmatched delimiter\n"), true);
	if (ft_check_parenthesis(token))
		return (printf("minishell: syntax error unmatched parenthesis.\n"), true);
	if (ft_check_redirects(token))
		return (printf("minishell: syntax error expected word after redirection\n"), true);
	if (ft_check_between_operator(token))
		return (printf("minishell: syntax error invalid combination or sequence of operators\n"), true);
	if (ft_check_open_parenthesis(token))
		return (printf("minishell: syntax error invalid opening parenthesis placement\n"), true);
	if (ft_check_close_parenthesis(token))
		return (printf("minishell: syntax error invalid closing parenthesis placement\n"), true);
	if (ft_check_if_have_parenthesis(token))
		return (printf("minishell: parenthesis must be implemented in the future\n"), true) ;
	return (false);
}

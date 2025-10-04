/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/12 22:50:49 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')' || c == '&');
}

void	ft_check_new_token(t_token *new_token, char *input, t_token *top)
{
	if (!new_token)
	{
		ft_free_input_token(input, top);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

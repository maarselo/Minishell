/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:41:56 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/03 21:21:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ');
}

int	ft_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	ft_is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_count_tokens(char *s)
{
	int	tkcount;
	int	i;

	tkcount = 0;
	i = 0;
	while (s[i])
	{
		while (ft_is_space(s[i]))
			i++;
		if (s[i] == '|')
		{
			tkcount++;
			i++;
		}
		else if (s[i] == '>' || s[i] == '<')
		{
			if (s[i] == s[i + 1])
				i++;
			tkcount++;
			i++;
		}
		else if (ft_is_quote(s[i]))
		{
			if (ft_is_space(s[i - 1]))
				tkcount++;
			i++;
			while (s[i] && !ft_is_quote(s[i]))
				i++;
			i++;
		}
		else
		{
			while (s[i] && !ft_is_space(s[i]) && !ft_is_quote(s[i])
				&& !ft_is_operator_start(s[i]))
				i++;
			tkcount++;
		}
	}
	return (tkcount);
}

t_token	**ft_get_tokens(char *input)
{
	t_token	**tokens;

	tokens = NULL;
	tokens = malloc((ft_count_tokens(input) + 1) * sizeof(t_token *));
	return (tokens);
}

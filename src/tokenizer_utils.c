/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/30 18:55:47 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
int	ft_find_char(int c, char *input)
{
	int i = -1;
	while (input[++i])
	{
		if (input[i] == 'c')
			return (1);
	}
	return (0);
}

int	ft_check_quotes(char *input)
{
	int	i;

	i = -1;
	while(input[++i])
	{
		if (input[i] == '\'')
		{
			if (!ft_find_char('\'', input + i))
				return (1);
		}
		else if(input[i] == '"')
		{
			if (!ft_find_char('"', input + i))
				return (1);
		}
	}
	return (0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:41:56 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/04 01:00:16 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_extract_word(char *str, int	*i)
{
	int	start;
	int	quotes;

	quotes = 0;
	start = *i;
	while (str[*i])
	{
		if (ft_is_quote(str[*i]) && quotes == 0)
			quotes = 1;
		else if (ft_is_quote(str[*i]) && quotes == 1)
			quotes = 0;
		if (ft_is_space(str[*i]) && quotes == 0)
			break ;
		if (ft_is_operator(str[*i]) && quotes == 0)
			break ;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	*ft_extract_quotes(char *str, int	*i)
{
	int		start;
	int		end;
	char	quote;

	quote = str[*i];
	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	end = *i;
	return (ft_substr(str, start, end - start));
}

char	*ft_extract_token(char *input, int *i)
{
	char	*token_str;

	if (ft_is_quote(input[*i]))
		return (ft_extract_quotes(input, i));
	else if (ft_is_operator(input[*i]))
	{
		if (input[*i] == '<' && input[*i + 1] == '<')
		{
			*i += 2;
			return (ft_strdup("<<"));
		}
		else if (input[*i] == '>' && input[*i + 1] == '>')
		{
			*i += 2;
			return (ft_strdup(">>"));
		}
		else
		{
			token_str = ft_substr(input, *i, 1);
			(*i)++;
			return (token_str);
		}
	}
	else
		return (ft_extract_word(input, i));
}

t_token	*ft_get_tokens(char *input)
{
	int		i;
	t_token	*head;
	t_token	*last;
	t_token	*new;
	char	*token_str;

	head = NULL;
	last = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		token_str = ft_extract_token(input, &i);
		if (!token_str)
			return (NULL);
		new = ft_init_token(token_str);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
	}
	ft_print_tokens(head);
	return (head);
}

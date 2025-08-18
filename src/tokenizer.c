/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/17 22:05:10 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*ft_extract_quotes(char *str, int	*i)
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

static char	*ft_extract_word(char *str, int	*i)
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
		if (ft_isspace(str[*i]) && quotes == 0)
			break ;
		if (ft_is_operator(str[*i]) && quotes == 0)
			break ;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

static char	*ft_extract_token(char *input, int *i)
{
	if (ft_is_quote(input[*i]))
		return (ft_extract_quotes(input, i));
	else if (ft_is_operator(input[*i]))
	{
		if (input[*i] == '<' && input[*i + 1] == '<')
			return (*i += 2, ft_strdup("<<"));
		else if (input[*i] == '>' && input[*i + 1] == '>')
			return (*i += 2, ft_strdup(">>"));
		else if (input[*i] == '|' && input[*i + 1] == '|')
			return (*i += 2, ft_strdup("||"));
		else if (input[*i] == '&' && input[*i + 1] == '&')
			return (*i += 2, ft_strdup("&&"));
		else
			return ((*i)++, ft_substr(input, *i - 1, 1));
	}
	else
		return (ft_extract_word(input, i));
}

t_token	*ft_tokenizer(char *input)
{
	int		i;
	char	*str_token;
	t_token	*new_token;
	t_token	*top;
	t_token	*bottom;

	i = 0;
	top = NULL;
	bottom = NULL;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		str_token = ft_extract_token(input, &i);
		if (!str_token)
			return (NULL);
		new_token = ft_init_token(str_token);
		if (!new_token)
			return (NULL);
		if (!top)
			top = new_token;
		else
			bottom->next = new_token;
		bottom = new_token;
	}
	return (top);
}

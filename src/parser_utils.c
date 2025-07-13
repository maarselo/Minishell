/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/13 18:59:02 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 
/*
int	ft_count_command(t_token *token_list)
{
	int	count;

	count = 1;
	while (token_list)
	{
		if (token_list->type == 1)
			count++;
		token_list = token_list->next;
	}
	return (count);
}

int	ft_check_start_end_types(t_token *token)// | || &&
{
	t_token	*tmp;
	
	tmp = token;
	if (tmp->type == 1 || tmp->type == 6 || tmp->type == 7)//check the first was, pipe, ||, &&
		return (1);
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == 1 || tmp->type == 6 || tmp->type == 7)//check the last command
		return (1);
	return (0);
}

static int	ft_check_content_delimiters(char *input)
{
	int	i;
	char delimiter_type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"' || input[i] == '(')
		{
			if (input[i] == '(')
				delimiter_type = ')';
			else
				delimiter_type = input[i];
			i++;
			while (input[i] && input[i] != delimiter_type)
				i++;
			if (input[i] != delimiter_type)
				return (1); 
		}
		i++;
	}
	return (0);
}

int	ft_check_delimiters(t_token *token) //'"(
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_check_content_delimiters(tmp->content))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_redirects(t_token *token)
{
	t_token	*tmp;
	
	tmp = token;
	while(tmp)
	{
		if (((tmp->type == 2 || tmp->type == 3 || tmp->type == 4
				|| tmp->type == 5)) && (!tmp->next || tmp->next->type != 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}*/
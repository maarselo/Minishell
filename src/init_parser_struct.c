/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:46:50 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/17 22:09:23 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*ft_create_redirection_struct(void)
{
	t_redirect	*redirections;

	redirections = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!redirections)
		return (NULL);
	return (redirections);
}

t_command	*ft_create_command_struct(void)
{
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	return (command);
}

char	**ft_alloc_argv_according_correct_t_words(t_token *start, t_token *end)
{
	int		total_twords;
	t_token	*tmp;
	t_token	*previous;
	char	**argv_command;

	tmp = start;
	total_twords = 0;
	while (tmp && tmp != end)
	{
		if (tmp->type == T_WORD)
		{
			if (start == tmp)
				previous = ft_get_previos_token(true, start, tmp);
			else
				previous = ft_get_previos_token(false, start, tmp);
			if (!ft_get_if_its_redirection_type(previous))
				total_twords++;
		}
		tmp = tmp->next;
	}
	if (total_twords == 0)
		return (NULL);
	argv_command = (char **)malloc(sizeof(char *) * (total_twords + 1));
	argv_command[total_twords] = NULL;
	return (argv_command);
}

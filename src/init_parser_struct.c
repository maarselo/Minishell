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

t_command	*ft_create_command_struct(void)
{
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
	{
		perror("minishell: ");
		return (NULL);
	}
	return (command);
}

t_redirect	*ft_create_redirection_struct(int *malloc_error)
{
	t_redirect	*redirections;

	redirections = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!redirections)
	{
		perror("minishell: ");
		*malloc_error = 1;
		return (NULL);
	}
	return (redirections);
}

char	*ft_strdup_with_flag(int *malloc_error, const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
	{
		perror("minishell: ");
		*malloc_error = 1;
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**ft_alloc_argv(int total_twords, int *malloc_error)
{
	char	**argv_command;

	argv_command = (char **)ft_calloc((total_twords + 1), sizeof(char *));
	if (!argv_command)
	{
		perror("minishell: ");
		*malloc_error = 1;
	}
	return (argv_command);
}

char	**ft_alloc_argv_according_words(int *malloc_error, t_token *start,
		t_token *end)
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
	argv_command = ft_alloc_argv(total_twords, malloc_error);
	return (argv_command);
}

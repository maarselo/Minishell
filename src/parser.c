/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:00:23 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/18 14:04:30 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirect	*ft_fill_redirecction(t_token *start, t_token *end)
{
	t_token		*tmp;
	t_redirect	*redirections;

	if (!ft_have_any_redirection(start, end))
		return (NULL);
	tmp = start;
	redirections = ft_create_redirection_struct();
	while (tmp && tmp != end)
	{
		if (tmp->type == T_REDIR_IN)
			ft_set_redirect_infile(tmp, redirections);
		else if (tmp->type == T_HEREDOC)
			ft_set_redirect_heredoc(tmp, redirections);
		else if (tmp->type == T_REDIR_OUT)
			ft_set_redirect_outfile(tmp, redirections);
		else if (tmp->type == T_REDIR_APPEND)
			ft_set_redirect_append(tmp, redirections);
		tmp = tmp->next;
	}
	return (redirections);
}

static char	**ft_fill_argv_command(t_token *start, t_token *end)
{
	int		i;
	char	**argv_command;
	t_token	*tmp;
	t_token	*previous;

	i = 0;
	tmp = start;
	argv_command = ft_alloc_argv_according_words(start, end);
	if (!argv_command)
		return (NULL);
	while (tmp && tmp != end)
	{
		if (tmp->type == T_WORD)
		{
			if (start == tmp)
				previous = ft_get_previos_token(true, start, tmp);
			else
				previous = ft_get_previos_token(false, start, tmp);
			if (!ft_get_if_its_redirection_type(previous))
				argv_command[i++] = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
	}
	return (argv_command);
}

static t_connector_type	ft_fill_connector_type(t_token *end)
{
	if (!end)
		return (0);
	else if (end->type == T_PIPE)
		return (PIPE_CONNECTOR);
	else if (end->type == T_AND)
		return (AND_CONNECTOR);
	else if (end->type == T_OR)
		return (OR_CONNECTOR);
	return (0);
}

static t_command	*ft_analyze_command_to_struct(t_token **init, t_token **end)
{
	t_command	*command;

	command = ft_create_command_struct();
	command->command = ft_fill_argv_command(*init, *end);
	command->redirection = ft_fill_redirecction(*init, *end);
	command->connector = ft_fill_connector_type(*end);
	if (*end)
	{
		*end = (*end)->next;
		*init = *end;
	}
	return (command);
}

t_command	*ft_tokens_to_command_struct(t_token *token_list)
{
	int			total_commands;
	t_token		*start;
	t_token		*end;
	t_command	*top_command_list;
	t_command	*command;

	total_commands = ft_count_command(token_list);
	start = token_list;
	end = token_list;
	top_command_list = NULL;
	while (end && total_commands)
	{
		while (!ft_check_if_end_command(end))
			end = end->next;
		command = ft_analyze_command_to_struct(&start, &end);
		if (!top_command_list)
			top_command_list = command;
		else
			ft_add_command_into_list(command, top_command_list);
		total_commands--;
	}
	return (top_command_list);
}
/*
void    ft_print_command_list(t_command *list)
{
    int i;
    int cmd_index = 1;

    while (list)
    {
        printf("=== Command %d ===\n", cmd_index);

        // ---- imprimir argv ----
        printf("argv:\n");
        if (list->command)
        {
            i = 0;
            while (list->command[i])
            {
                printf("\t[%d] -> %s\n", i, list->command[i]);
				printf("len: %ld", ft_strlen(list->command[i]));
                i++;
            }
        }
        else
            printf("\t(NULL)\n");

        // ---- imprimir redirection ----
        printf("redirection:\n");
        if (list->redirection)
        {
            printf("\tinfile: %s\n",
                list->redirection->infile ? list->redirection->infile : "(NULL)");
            printf("\toutfile: %s\n",
                list->redirection->outfile ? list->redirection->outfile : "(NULL)");
            printf("\tappend: %d\n", list->redirection->append);
            printf("\theredoc: %d\n", list->redirection->heredoc);
            printf("\tdelimiter: %s\n",
                list->redirection->delimiter ? list->redirection->delimiter : "(NULL)");
        }
        else
            printf("\t(NULL)\n");

        // ---- imprimir connector ----
        printf("connector: %d\n", list->connector);

        // avanzar
        list = list->next;
        cmd_index++;
    }
}*/
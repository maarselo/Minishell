/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:57:46 by mvillavi          #+#    #+#             */
/*   Updated: 2025/10/02 20:16:05 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_and_input(char *input, t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	if (input)
		free(input);
	current = token_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

void	ft_free_token_list(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

void	ft_free_envp(t_env *envp)
{
	t_env 	*tmp;
	t_env	*next;

	tmp = envp;
	while (tmp)
	{	
		next = tmp->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
}

void	ft_free_command_list(t_command *command_list)
{
	t_command	*tmp;
	t_command	*next;

	tmp = command_list;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (tmp->command)
			ft_free_argv_command(tmp->command);
		if (tmp->redirection)
			ft_free_redirections_command(tmp->redirection);
		free(tmp);
		tmp = next;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while(split[++i])
		free(split[i]);
	free(split);
}

void	ft_free_envp(t_env *envp)
{
	t_env	*tmp;
	t_env	*next;
	tmp = envp;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
}

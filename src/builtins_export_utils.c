/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:22:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 17:59:08 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_clone_env_node(t_env *tmp)
{
	t_env	*node;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (perror("minishell: "),
			ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
	if (tmp->value)
	{
		node->value = ft_strdup(tmp->value);
		if (!node->value)
			return (ft_set_global_exit_status(T_GENERAL_ERROR),
				free(node), NULL);
	}
	if (tmp->name)
	{
		node->name = ft_strdup(tmp->name);
		if (!node->name)
			return (free(node->value), free(node),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
	}
	return (node);
}

static void	ft_insert_node_sorted(t_env *node, t_env **sorted)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	if (!*sorted || ft_strcmp((*sorted)->name, node->name) > 0)
	{
		node->next = *sorted;
		*sorted = node;
		return ;
	}
	current = *sorted;
	while (current && ft_strcmp(current->name, node->name) <= 0)
	{
		previous = current;
		current = current->next;
	}
	previous->next = node;
	node->next = current;
}

t_env	*ft_clone_env_list(t_data *data)
{
	t_env	*tmp;
	t_env	*node;
	t_env	*sorted;

	sorted = NULL;
	tmp = data->env;
	while (tmp)
	{
		node = ft_clone_env_node(tmp);
		if (!node)
			return (ft_free_envp(sorted), NULL);
		ft_insert_node_sorted(node, &sorted);
		tmp = tmp->next;
	}
	return (sorted);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:19:54 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 18:50:10 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_insert_node_sorted(t_env *node, t_env **sorted)
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

t_env	*ft_clone_env_node(t_env *tmp)
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

t_env	*ft_clone_env_list(t_env *env_list)
{
	t_env	*tmp;
	t_env	*node;
	t_env	*sorted;

	sorted = NULL;
	tmp = env_list;
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

void	ft_check_env_node(char *var_value, t_env *node_env)
{
	if (!node_env->name)
		return (perror("minishell :"), free(node_env),
			ft_set_global_exit_status(T_GENERAL_ERROR));
	node_env->value = ft_strdup(var_value);
	if (!node_env->value)
		return (perror("minishell: "), free(node_env->name), free(node_env),
			ft_set_global_exit_status(T_GENERAL_ERROR));
}

t_env	*ft_create_node_export_by_mode(char *mode, char *var_name, char *var_value)
{
	t_env	*node_env;

	node_env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!ft_strcmp(mode, NO_VALUE))
	{
		node_env->name = ft_strdup(var_name);
		if (!node_env->name)
			return (perror("minishell :"), free(node_env),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
		ft_set_global_exit_status(T_SUCCESS);
	}
	else if (!ft_strcmp(mode, NULL_VALUE))
	{
		node_env->name = ft_strdup(var_name);
		ft_check_env_node(var_value, node_env);
	}
	else if (!ft_strcmp(mode, WITH_VALUE))
	{
		node_env->name = ft_strdup(var_name);
		ft_check_env_node(var_value, node_env);
	}
	return (node_env);
}

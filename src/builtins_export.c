/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:22:25 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/04 17:29:17 by fbanzo-s         ###   ########.fr       */
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

t_env	*ft_clone_env_list(t_env *env_list)
{
	t_env	*tmp;
	t_env	*node;
	t_env	*sorted;

	sorted = NULL;
	tmp = env_list;
	while (tmp)
	{
		node = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!node)
			return (perror("minishell: "),
				ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
		if (tmp->value)
		{
			node->value = ft_strdup(tmp->value);
			if (!node->value)
				return (ft_free_envp(sorted), ft_free_envp(env_list),
					ft_set_global_exit_status(T_GENERAL_ERROR),
					free(node), NULL);
		}
		if (tmp->name)
		{
			node->name = ft_strdup(tmp->name);
			if (!node->name)
				return (ft_free_envp(sorted), ft_free_envp(env_list),
					free(node->value), free(node),
					ft_set_global_exit_status(T_GENERAL_ERROR), NULL );
		}
		ft_insert_node_sorted(node, &sorted);
		tmp = tmp->next;
	}
	return (sorted);
}

void	ft_print_order_variables(t_env *list)
{
	t_env	*order_env;
	t_env	*tmp;

	order_env = ft_clone_env_list(list);
	if (!order_env)
		return ;
	tmp = order_env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\'%s\'\n", tmp->name, tmp->value);
		else
			printf("declare -x %s=\'\'\n", tmp->name);
		tmp = tmp->next;
	}
}

void	ft_add_var_into_list(t_env *env, t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = env;
}

int	ft_create_and_add_variable(char *mode, char *command, t_env *env_list)
{
	t_env	*env;
	char	*name_var;
	char	*new_value;

	name_var = ft_split_name_var(command);
	new_value = ft_split_value_var(command);
	if (ft_find_env_var_name(env_list, name_var) == 0)
	{
		ft_replace_env_var(env_list, name_var, new_value);
		return (0);
	}
	env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!ft_strcmp(mode, NO_VALUE))
	{
		env->name = ft_strdup(command);
		if (!env->name)
			return (perror("minishell :"), free(env),
				ft_set_global_exit_status(T_GENERAL_ERROR), 1);
		ft_add_var_into_list(env, env_list);
		ft_set_global_exit_status(T_SUCCESS);
	}
	else if (!ft_strcmp(mode, NULL_VALUE))
	{
		env->name = ft_strndup(command, ft_strlen(command) - 1);
		if (!env->name)
			return (perror("minishell :"), free(env),
				ft_set_global_exit_status(T_GENERAL_ERROR), 1);
		env->value = ft_strdup("");
		if (!env->value)
			return (perror("minishell :"), free(env->name), free(env),
				ft_set_global_exit_status(T_GENERAL_ERROR), 1);
		ft_add_var_into_list(env, env_list);
	}
	else if (!ft_strcmp(mode, WITH_VALUE))
	{
		env->name = ft_substr(command, 0, ft_strchr(command, '=') - command);
		if (!env->name)
			return (perror("minishell :"), free(env),
				ft_set_global_exit_status(T_GENERAL_ERROR), 1);
		env->value = ft_substr(command, ft_strlen(env->name) + 1,
				ft_strlen(command) - ft_strlen(env->name) - 1);
		if (!env->value)
			return (perror("minishell: "), free(env->name), free(env),
				ft_set_global_exit_status(T_GENERAL_ERROR), 1);
		ft_add_var_into_list(env, env_list);
	}
	return (0);
}

void	ft_export(char **command, t_env *env_list)
{
	int		i;

	i = 1;
	if (!command[1])
	{
		ft_print_order_variables(env_list);
		ft_set_global_exit_status(T_SUCCESS);
		return ;
	}
	while (command[i])
	{
		if (ft_isdigit(command[i][0]) || command[i][0] == '='
			|| ft_contains_metachar(command[i]))
		{
			printf("minishell: export: `%s`: not a valid identifier\n",
				command[i]);
			ft_set_global_exit_status(T_GENERAL_ERROR);
		}
		else if (!ft_strchr(command[i], '=') && ft_is_all_asnum(command[i]))
		{
			if (ft_create_and_add_variable(NO_VALUE, command[i], env_list))
				return ;//malloc error
			ft_set_global_exit_status(T_SUCCESS);
		}
		else if (ft_strchr(command[i], '=')
			&& (command[i][ft_strlen(command[i]) - 1] == '='))
		{
			if (ft_create_and_add_variable(NULL_VALUE, command[i], env_list))
				return ;//manage error
			ft_set_global_exit_status(T_SUCCESS);
		}
		else if (ft_strchr(command[i], '=')
			&& (command[i][ft_strlen(command[i]) - 1] != '='))
		{
			if (ft_create_and_add_variable(WITH_VALUE, command[i], env_list))
				return ;//manage error
			ft_set_global_exit_status(T_SUCCESS);
		}
		i++;
	}
}

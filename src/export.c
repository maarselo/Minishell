/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/09/23 16:25:16 by fbanzo-s         ###   ########.fr       */
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
	previous->next;
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
		node = (t_env *)ft_calloc(sizeof(t_env *), 1);
		if (!node)
			return (perror("minishell: "), ft_set_global_exit_status(T_GENERAL_ERROR), NULL);
		if (tmp->value)
			node->value = ft_strdup(tmp->value);
		if (!node->value)
			return (ft_free_envp(sorted), ft_free_envp(env_list), free(node), ft_set_global_exit_status(T_GENERAL_ERROR), NULL );
		if (tmp->name)
			node->name = ft_strdup(tmp->name);
		if (!node->name)
			return (ft_free_envp(sorted), ft_free_envp(env_list), free(node->value), free(node), ft_set_global_exit_status(T_GENERAL_ERROR), NULL );
		ft_insert_env_sorted(node, &sorted);
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
		printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
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

	env = (char *)ft_calloc(sizeof(t_env *), 1);

	if (!ft_strcmp(mode, NO_VALUE))
	{
		env->name = ft_strdup(command);
		if (!env->name)
			return (perror("minishell :"), ft_set_global_exit_status(T_GENERAL_ERROR), free(env), 1);
		ft_add_var_into_list(env, env_list);
		ft_set_global_exit_status(T_SUCCESS);
	}
	else if (!ft_strcmp(mode, NULL_VALUE))
	{
		env->name = ft_strdup(command);
		if (!env->name)
			return (perror("minishell :"),ft_set_global_exit_status(T_GENERAL_ERROR) ,free(env), 1);
		env->value = ft_strdup("");
		if (!env->value)
			return (perror("minishell :"),ft_set_global_exit_status(T_GENERAL_ERROR) ,free(env->name), free(env), 1);
		ft_add_var_into_list(env, env_list);
	}
	else if (!ft_strcmp(mode, WITH_VALUE))
	{
		env->name = ft_substr(command, 0, ft_strchr(command, '=') - command);
		if (!env->name)
			return (perror("minishell :"),ft_set_global_exit_status(T_GENERAL_ERROR) , free(env), 1);
		env->value = ft_substr(command, ft_strlen(env->name) + 1, ft_strlen(command)- ft_strlen(env->name) - 1);
		if (!env->value)
			return (perror("minishell: "),ft_set_global_exit_status(T_GENERAL_ERROR) , free(env->name), free(env), 1);
	}
	return (0);
}

//idk if i need to manage exportvar=hola export
void	ft_export(char **command, t_env *env_list)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = env_list;
	if (!ft_strncmp(command[0], "export", ft_strlen("export") && !command[1]))
	{
		ft_print_order_variables(env_list);
		ft_set_global_exit_status(T_SUCCESS);
		return ;
	}
	while (command[i])
	{
		if (ft_isdigit(command[i][0]) || command[i][0] == '=' || !ft_contains_metachar(command[i]))
		{
			printf("minishell: export: `%s`: not a valid identifier\n");
			ft_set_global_exit_status(T_GENERAL_ERROR);
		}
		else if (!ft_strchr(command[i], '=') && ft_is_all_asnum(command[i]))
		{
			if (ft_add_var_without_value(command[i], env_list))
				return ;//malloc error
			ft_set_global_exit_status(T_SUCCESS);
		}
		else if (ft_strchr(command[i], '=') && (command[i][ft_strlen(command[i]) - 1] == '='))
		{
			if (ft_add_var_with_null_value(command[i], env_list))
				return ;//manage error
			ft_set_global_exit_status(T_SUCCESS);
		}
		else if (ft_strchr(command[i], '=') && (command[i][ft_strlen(command[i]) - 1] != '='))
		{
			if (ft_add_var_with_value(command[i], env_list))
				return ; //manage error
			ft_set_global_exit_status(T_SUCCESS);
		}
	}
}
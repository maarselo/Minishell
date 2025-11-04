/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:53:36 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/04 17:24:52 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_value_length(char *env_var, int i)
{
	int	l;

	l = 0;
	while (env_var[i])
	{
		l++;
		i++;
	}
	return (l);
}

t_env	*ft_create_env_node(char *name, char *value)
{
	t_env	*var;

	var = (t_env *)malloc(sizeof(t_env));
	if (!var)
		return (perror("Error allocating memory\n"), exit(8), NULL);
	var->name = ft_strdup(name);
	if (!var->name)
	{
		free(var);
		return (NULL);
	}
	if (value)
	{
		var->value = ft_strdup(value);
		if (!var->value)
		{
			free(var->name);
			free(var);
			return (NULL);
		}
	}
	else
		var->value = NULL;
	var->next = NULL;
	return (var);
}

void	ft_add_env_var(t_env **env_list, char *name, char *value)
{
	t_env	*new_node;
	t_env	*current;

	if (!env_list || !name)
		return ;
	new_node = ft_create_env_node(name, value);
	if (!new_node)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	ft_find_env_var_name(t_env *env_list, char *name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

char	*ft_set_var_value(char *name, char *env_var)
{
	char	*value;
	char	*tmp;

	if (ft_strcmp(name, "SHLVL") == 0)
	{
		tmp = ft_get_value_env(env_var);
		value = ft_itoa(ft_atoi(tmp) + 1);
		free(tmp);
	}
	else
		value = ft_get_value_env(env_var);
	return (value);
}

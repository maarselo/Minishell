/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:02:03 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/17 20:32:24 by fbanzo-s         ###   ########.fr       */
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

char	*ft_get_name_env(char *env_var)
{
	char	*name;
	int		i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (perror("Error allocating memory\n"), exit(8), NULL);
	i = 0;
	while (env_var[i] && env_var[i] != '=')
	{
		name[i] = env_var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_get_value_env(char *env_var)
{
	char	*value;
	int		i;
	int		j;
	int		l;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	i++;
	j = i;
	l = ft_get_value_length(env_var, i);
	value = malloc(sizeof(char) * l + 1);
	if (!value)
		return (perror("Error allocating memory\n"), exit(8), NULL);
	i = 0;
	while (env_var[j])
	{
		value[i] = env_var[j];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

t_env	*ft_init_env(char *env_var)
{
	t_env	*var;

	var = (t_env *)malloc(sizeof(t_env));
	if (!var)
		return (perror("Error allocating memory\n"), exit(8), NULL);
	if (!ft_strchr(env_var, '='))
	{
		var->name = ft_strdup(env_var);
		if (!var->name)
			return (perror("Error allocating memory\n"), exit(8), NULL);
		var->value = NULL;
	}
	else
	{
		var->name = ft_get_name_env(env_var);
		var->value = ft_get_value_env(env_var);
	}
	var->next = NULL;
	return (var);
}

t_env	*ft_get_env(char **envp)
{
	t_env	*var;
	t_env	*next_var;
	int		i;

	var = ft_init_env(envp[0]);
	next_var = var;
	i = 1;
	while (envp[i])
	{
		next_var->next = ft_init_env(envp[i]);
		next_var = next_var->next;
		i++;
	}
	return (var);
}

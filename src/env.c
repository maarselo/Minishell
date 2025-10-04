/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:07:12 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/04 17:17:43 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strcmp(var->name, "SHLVL") == 0)
			var->value = ft_itoa(ft_atoi(ft_get_value_env(env_var)) + 1);
		else
			var->value = ft_get_value_env(env_var);
	}
	var->next = NULL;
	return (var);
}

t_env	*ft_init_min_env(char **envp)
{
	t_env	*env_list;
	char	*cwd;

	env_list = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_add_env_var(&env_list, "PWD", cwd);
		free(cwd);
	}
	ft_add_env_var(&env_list, "SHLVL", "1");
	ft_add_env_var(&env_list, "OLDPWD", "");
	return (env_list);
}

t_env	*ft_get_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	if (!envp || !*envp)
		return (ft_init_min_env(NULL));
	head = ft_init_env(envp[0]);
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (envp[i])
	{
		current->next = ft_init_env(envp[i]);
		current = current->next;
		i++;
	}
	current->next = NULL;
	return (head);
}

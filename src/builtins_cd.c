/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:23:42 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 20:33:20 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env_var(t_env *env_list, char *name, char *value)
{
	t_env	*var;

	var = env_list;
	while (var)
	{
		if (ft_strcmp(var->name, name) == 0)
		{
			if (var->value)
				free(var->value);
			if (value)
				var->value = value;
			else
				var->value = NULL;
			return ;
		}
		var = var->next;
	}
}

void	ft_update_pwd(char *new_path, t_env *env_list)
{
	t_env	*var;
	char	*old_path;

	var = env_list;
	while (var)
	{
		if (ft_strcmp(var->name, "PWD") == 0)
		{
			old_path = ft_strdup(var->value);
			break ;
		}
		var = var->next;
	}
	ft_set_env_var(env_list, "OLDPWD", old_path);
	ft_set_env_var(env_list, "PWD", new_path);
	if (old_path)
		free(old_path);
}

void	ft_cd(char **args, t_env *env_list)
{
	char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			ft_set_global_exit_status(T_GENERAL_ERROR);
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		ft_set_global_exit_status(T_GENERAL_ERROR);
	}
	else
	{
		ft_update_pwd(path, env_list);
        ft_set_global_exit_status(T_SUCCESS);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:23:42 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 16:10:02 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_env_var(char *name, char *value, t_data *data)
{
	t_env	*var;

	var = data->env;
	while (var)
	{
		if (ft_strcmp(var->name, name) == 0)
		{
			if (var->value)
				free(var->value);
			if (value)
			{
				var->value = ft_strdup(value);
				if (!var->value)
					ft_perror_free_data_exit(data, T_GENERAL_ERROR);
			}
			else
				var->value = NULL;
			return ;
		}
		var = var->next;
	}
}

static void	ft_update_pwd(char *new_path, t_data *data)
{
	t_env	*var;
	char	*old_path;

	old_path = NULL;
	var = data->env;
	while (var)
	{
		if (ft_strcmp(var->name, "PWD") == 0)
		{
			if (var->value)
			{
				old_path = ft_strdup(var->value);
				if (!old_path)
					ft_perror_free_data_exit(data, T_GENERAL_ERROR);
			}
			break ;
		}
		var = var->next;
	}
	ft_set_env_var("OLDPWD", old_path, data);
	ft_set_env_var("PWD", new_path, data);
	if (old_path)
		free(old_path);
}

void	ft_cd(char **args, t_data *data)
{
	char	*path;

	if (!args[1])
	{
		path = ft_acces_env_value("HOME", data->env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			ft_set_global_exit_status(data, T_GENERAL_ERROR);
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		ft_set_global_exit_status(data, T_GENERAL_ERROR);
	}
	else
	{
		ft_update_pwd(path, data);
		ft_set_global_exit_status(data, T_SUCCESS);
	}
}

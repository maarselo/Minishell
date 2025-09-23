/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:23:42 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/09/23 16:58:26 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_pwd(char *path, t_env *env_list)
{
	t_env	*var;

	var = env_list;
	while (var)
	{
		if (ft_strcmp(var->name, "PWD") == 0)
		{
			if (var->value)
				free(var->value);
			var->value = ft_strdup(path);
			break ;
		}
		var = var->next;
	}
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
			g_status.exit_status = 1;
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		g_status.exit_status = 1;
	}
	else
	{
		ft_update_pwd(path, env_list);
        g_status.exit_status = 0;
	}
}

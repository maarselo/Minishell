/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:14:46 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/02 04:16:54 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && ft_isalpha(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_env	*ft_remove_env_var(char *str, t_env *env_list)
{
	t_env	*current;
	t_env	*prev;

	current = env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, str) == 0)
			break ;
		prev = current;
		current = current->next;
	}
	if (!current)
		return (env_list);
	if (prev)
		prev->next = current->next;
	else
		env_list = current->next;
	if (current->name)
		free(current->name);
	if (current->value)
		free(current->value);
	free(current);
	return (env_list);
}

void	ft_unset(char **args, t_env **env_list)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		g_status.exit_status = 0;
		return ;
	}
	while (args[i])
	{
		if (ft_is_valid_var_name(args[i]) == 1)
		{
			perror("minishell: unset");
			g_status.exit_status = 1;
		}
		*env_list = ft_remove_env_var(args[i], *env_list);
		i++;
	}
	g_status.exit_status = 0;
}

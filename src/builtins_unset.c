/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:14:46 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 16:19:39 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_remove_env_var(char *str, t_env *env_list)
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

void	ft_unset(t_data *data, char **args, t_env **env_list)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		ft_set_global_exit_status(data, T_SUCCESS);
		return ;
	}
	while (args[i])
	{
		*env_list = ft_remove_env_var(args[i], *env_list);
		i++;
	}
	ft_set_global_exit_status(data, T_SUCCESS);
}

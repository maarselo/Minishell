/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:07:31 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/13 19:58:09 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_expand(t_cmd *cmd, t_env *env_list, int status)
{
	while (cmd)
	{

	}
}

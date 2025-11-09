/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_variables1_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:03:16 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/09 00:54:24 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_append_shlvl(t_env *env_node, int number)
{
	char	*str_number;
	char	*tmp;

	tmp = env_node->value;
	str_number = ft_itoa(number);
	env_node->value = ft_itoa(ft_atoi(env_node->value) + ft_atoi(str_number));
	free(tmp);
	free(str_number);
	if (ft_atoi(env_node->value) > 1000)
	{
		free(env_node->value);
		env_node->value = ft_strdup("1");
		ft_printf_fd(2,
			"minishell: shell level too high, resetting to 1\n");
	}
}

void	ft_find_shlvl(t_env *env_node, char *mode, int number)
{
	while (env_node)
	{
		if (!ft_strcmp(env_node->name, "SHLVL"))
		{
			if (!ft_strcmp(mode, MODE_WRITE))
			{
				free(env_node->value);
				env_node->value = ft_itoa(number);
			}
			else if (!ft_strcmp(mode, MODE_APPEND))
			{
				ft_append_shlvl(env_node, number);
			}
		}
		env_node = env_node->next;
	}
}

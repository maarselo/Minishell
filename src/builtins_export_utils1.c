/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:19:54 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/04 23:06:35 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_split_name_var(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (ft_strndup(str, i));
}

char	*ft_split_value_var(char *str)
{
	int		index;
	int		start;
	int		len;

	index = 0;
	start = 0;
	len = 0;
	while (str[index])
	{
		if (str[index] == '=')
			break ;
		index++;
		start++;
	}
	while (str[index])
	{
		index++;
		len++;
	}
	return (ft_substr(str, start + 1, len));
}

void	ft_replace_env_var(t_env *env_list, char *name_var, char *new_val)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name_var) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_val);
			break ;
		}
		current = current->next;
	}
}

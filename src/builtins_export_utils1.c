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

static int	ft_strlen_without_quotes(char *str)
{
	int	i;
	int	total;

	i = -1;
	total = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			continue ;
		total++;
	}
	return (total);
}

static char	*ft_remove_quotes(char *str)
{
	int		index;
	int		new_index;
	char	*new_str;

	index = -1;
	new_index = 0;
	new_str = ft_calloc(1, ft_strlen_without_quotes(str) + 1);
	while (str[++index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			continue ;
		new_str[new_index] = str[index];
		new_index++;
	}
	return (new_str);
}

char	*ft_split_name_var(char *str)
{
	int		i;
	char	*tmp;
	char	*var_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	var_name = ft_strndup(str, i);
	if (!ft_strchr(var_name, '\'') && !ft_strchr(str, '\"'))
		return (var_name);
	tmp = var_name;
	var_name = ft_remove_quotes(var_name);
	return (free(tmp), var_name);
}

char	*ft_split_value_var(char *str)
{
	int		index;
	int		start;
	int		len;
	char	*tmp;
	char	*value;

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
	value = ft_substr(str, start + 1, len);
	if (!ft_strchr(value, '\'') && !ft_strchr(value, '\"'))
		return (value);
	tmp = value;
	value = ft_remove_quotes(value);
	return (free(tmp), value);
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

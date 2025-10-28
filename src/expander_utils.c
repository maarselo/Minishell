/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:20:11 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/28 21:57:10 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_tilde(char *result, t_env *env_list)
{
	char	*tmp;

	if (!result)
		return (NULL);
	tmp = ft_get_env_value(env_list, "HOME");
	if (!tmp)
		return (ft_strdup(result));
	result = ft_join_str_var(result, tmp);
	free(tmp);
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_join_char_var(char *str, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(str, tmp);
	free(str);
	if (!joined)
		return (NULL);
	return (joined);
}

char	*ft_join_str_var(char *str, char *to_append)
{
	char	*joined;

	if (!to_append)
		to_append = "";
	joined = ft_strjoin(str, to_append);
	free(str);
	if (!joined)
		return (NULL);
	return (joined);
}

char	*ft_get_env_value(t_env *env_list, char *name_var)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name_var) == 0)
			break ;
		current = current->next;
	}
	if (!current)
		return (NULL);
	if (!current->value)
		return (ft_strdup(""));
	return (ft_strdup(current->value));
}

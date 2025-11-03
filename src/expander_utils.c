/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:20:11 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/03 01:11:37 by fbanzo-s         ###   ########.fr       */
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

	if (!str)
		return (NULL);
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

void	ft_process_command_arg(t_data *data, t_command *tmp,
			int *i, bool *quotes)
{
	char	*expanded;

	if (ft_strchr(tmp->command[*i], '\'')
		|| ft_strchr(tmp->command[*i], '"'))
		*quotes = true;
	expanded = ft_execute_expander(data, tmp->command[*i]);
	if (!expanded)
		ft_free_data_exit(data, T_GENERAL_ERROR);
	free(tmp->command[*i]);
	tmp->command[*i] = expanded;
	if (*quotes == false && ft_strchr(tmp->command[*i], '*'))
		ft_execute_wildcards(data, tmp, i);
	else
		(*i)++;
}

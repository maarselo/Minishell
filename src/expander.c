/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:07:31 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/06 16:43:33 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var(char *str, int *i, t_env *env_list)
{
	char	*value;
	char	*var;
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		value = ft_itoa(g_status.exit_status);
		if (!value)
			return (NULL);
		return (value);
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	if (!var)
		return (NULL);
	value = ft_get_env_value(env_list, var);
	free(var);
	if (value)
		return (value);
	return (ft_strdup(""));
}

char	*ft_expand_variables(char *str, t_env *env_list)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result = ft_handle_expansion(result, str, &i, env_list);
		if (!result)
		{
			free(str);
			return (NULL);
		}
	}
	free(str);
	return (result);
}

char	*ft_expand_var_no_quotes(char *str, t_env *env_list)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '~' && (str[i + 1] == '\0'
				|| str[i + 1] == '/' || ft_isspace(str[i + 1])))
		{
			result = ft_expand_tilde(result, env_list);
			if (!result)
				return (NULL);
			i++;
			continue ;
		}
		result = ft_handle_expansion(result, str, &i, env_list);
		if (!result)
			return (NULL);
	}
	free(str);
	return (result);
}

char	*ft_execute_expander(t_data *data, char *str)
{
	int	l;

	if (!str)
		return (NULL);
	l = ft_strlen(str);
	if (l >= 2 && str[0] == '\'' && str[l - 1] == '\'')
		return (ft_strndup(str + 1, l - 2));
	if (l >= 2 && str[0] == '"' && str[l - 1] == '"')
		return (ft_expand_variables(ft_strndup(str + 1, l - 2), data->env));
	return (ft_expand_var_no_quotes(ft_strdup(str), data->env));
}

void	ft_expand(t_data *data)
{
	int			i;
	char		*expanded;
	bool		quotes;
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		i = 0;
		quotes = false;
		while (tmp->command && tmp->command[i])
		{
			if (ft_strchr(tmp->command[i], '\'')
				|| ft_strchr(tmp->command[i], '"'))
				quotes = true;
			expanded = ft_execute_expander(data, tmp->command[i]);
			if (!expanded)
				ft_exit_free_data(data, T_GENERAL_ERROR);
			free(tmp->command[i]);
			tmp->command[i] = expanded;
			if (quotes == false && ft_strchr(tmp->command[i], '*'))
				ft_execute_wildcards(data, tmp, &i);
			else
				i++;
		}
		tmp = tmp->next;
	}
}

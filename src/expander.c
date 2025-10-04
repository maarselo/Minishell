/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:07:31 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/04 17:13:55 by fbanzo-s         ###   ########.fr       */
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
		return (ft_itoa(g_status.exit_status));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = ft_get_env_value(env_list, var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*ft_expand_variables(char *str, t_env *env_list)
{
	int		i;
	char	*result;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		result = ft_handle_expansion(result, str, &i, env_list);
	}
	return (result);
}

char	*ft_expand_var_no_quotes(char *str, t_env *env_list)
{
	int		i;
	char	*result;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '~' && (str[i + 1] == '\0'
				|| str[i + 1] == '/' || ft_isspace(str[i + 1])))
		{
			result = ft_expand_tilde(result, env_list);
			i++;
			continue ;
		}
		result = ft_handle_expansion(result, str, &i, env_list);
	}
	return (result);
}

char	*ft_execute_expander(char *str, t_env *env_list)
{
	int	l;

	if (!str)
		return (NULL);
	l = ft_strlen(str);
	if (l >= 2 && str[0] == '\'' && str[l - 1] == '\'')
		return (ft_strndup(str + 1, l - 2));
	if (l >= 2 && str[0] == '"' && str[l - 1] == '"')
		return (ft_expand_variables(ft_strndup(str + 1, l - 2), env_list));
	return (ft_expand_var_no_quotes(str, env_list));
}

void	ft_expand(t_command *cmd, t_env *env_list)
{
	int		i;
	char	*expanded;
	bool	quotes;

	while (cmd)
	{
		i = 0;
		quotes = false;
		while (cmd->command && cmd->command[i])
		{
			if (ft_strchr(cmd->command[i], '\'')
				|| ft_strchr(cmd->command[i], '"'))
				quotes = true;
			expanded = ft_execute_expander(cmd->command[i], env_list);
			free(cmd->command[i]);
			cmd->command[i] = expanded;
			if (quotes == false && ft_strchr(cmd->command[i], '*'))
				ft_execute_wildcards(cmd, &i);
			else
				i++;
		}
		cmd = cmd->next;
	}
}

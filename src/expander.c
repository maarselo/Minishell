/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:07:31 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 13:35:35 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var(char *str, int *i, t_env *env_list, int exit_status)
{
	char	*value;
	char	*var;
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(exit_status));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = getenv(var);
	return (ft_strdup(value));
}

char	*ft_expand_variables(char *str, t_env *env_list, int exit_status)
{
	int		i;
	char	*tmp;
	char	*result;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_expand_var(str, &i, env_list, exit_status);
			result = ft_join_str_var(result, tmp);
			free(tmp);
		}
		else
		{
			result = ft_join_char_var(result, str[i]);
			i++;
		}
	}
	return (result);
}

char	*ft_expand_var_no_quotes(char *str, t_env *env_list, int exit_status)
{
	int		i;
	char	*tmp;
	char	*result;

	result = ft_strdup("");
	i = 0;
	if (str[i] == '~' && (ft_isspace(str[i + 1]) || str[i + 1] == '/'))
		ft_expand_tilde(result);
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_expand_var(str, &i, env_list, exit_status);
			result = ft_join_str_var(result, tmp);
			free(tmp);
		}
		else
		{
			result = ft_join_char_var(result, str[i]);
			i++;
		}
	}
	return (result);
}

char	*ft_execute_expander(char *str, t_env *env_list, int exit_status)
{
	int	l;

	if (!str)
		return (NULL);
	l = ft_strlen(str);
	if (l >= 2 && str[0] == '\'' && str[l - 1] == '\'')
		return (ft_strndup(str + 1, l - 2));
	if (l >= 2 && str[0] == '"' && str[l - 1] == '"')
		return (ft_expand_variables(ft_strndup(str + 1, l - 2), env_list,
				exit_status));
	return (ft_expand_var_no_quotes(str, env_list, exit_status));
}

void	ft_expand(t_command *cmd, t_env *env_list, int exit_status)
{
	int		i;
	char	*expanded;

	while (cmd)
	{
		i = 0;
		while (cmd->command && cmd->command[i])
		{
			expanded = ft_execute_expander(cmd->command[i], env_list,
					exit_status);
			free(cmd->command[i]);
			cmd->command[i] = expanded;
			i++;
		}
		cmd = cmd->next;
	}
}

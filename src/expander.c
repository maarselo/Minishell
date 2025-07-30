/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:07:31 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/07/31 00:00:01 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_str_var(char *str, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	free(str);
	return (ft_strjoin(str, tmp));
}

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
			result = ft_join_str_var(result, str[i]);
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
		return (ft_strndup(str + 1, l 	- 2));
	if (l >= 2 && str[0] == '"' && str[l - 1] == '"')
		return (ft_expand_variables(ft_strndup(str + 1, l - 2), env_list,
				exit_status));
	return (ft_expand_variables(str, env_list, exit_status));
}

void	ft_expand(t_cmd *cmd, t_env *env_list, int exit_status)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			cmd->argv[i] = ft_execute_expander(cmd->argv[i], env_list,
					exit_status);
			i++;
		}
		cmd = cmd->next;
	}
}

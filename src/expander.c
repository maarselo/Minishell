/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:07:31 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/06 20:02:18 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_question_mark(t_data *data, int *i)
{
	char	*value;

	(*i)++;
	value = ft_itoa(data->exit_status);
	if (!value)
		return (NULL);
	return (value);
}

char	*ft_expand_var(char *str, int *i, t_data *data)
{
	char	*value;
	char	*var;
	int		start;

	(*i)++;
	if (str[*i] == '\0'
		|| (!ft_isalnum(str[*i]) && str[*i] != '_' && str[*i] != '?'))
		return (ft_strdup("$"));
	if (str[*i] == '?')
		value = ft_expand_question_mark(data, i);
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	if (!var)
		return (NULL);
	value = ft_get_env_value(data->env, var);
	free(var);
	if (value)
		return (value);
	return (ft_strdup(""));
}

char	*ft_expand_join(char *str, int *i, char *result, t_data *data)
{
	char	*tmp;
	bool	in_quotes;
	bool	in_squotes;

	in_quotes = false;
	in_squotes = false;
	while (str[*i])
	{
		if (str[*i] == '\'' && in_quotes == false)
			in_squotes = !in_squotes;
		else if (str[*i] == '"' && in_squotes == false)
			in_quotes = !in_quotes;
		if (str[*i] == '$' && in_squotes == false)
		{
			tmp = ft_expand_var(str, i, data);
			result = ft_join_str_var(result, tmp);
			free(tmp);
			continue ;
		}
		else
			result = ft_join_char_var(result, str[*i]);
		(*i)++;
	}
	return (result);
}

char	*ft_execute_expander(t_data *data, char *str)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	if (i == 0 && str[i] == '~' && (str[i + 1] == '\0'
			|| str[i + 1] == '/' || ft_isspace(str[i + 1])))
	{
		result = ft_expand_tilde(result, data->env);
		if (!result)
			return (NULL);
		i++;
	}
	result = ft_expand_join(str, &i, result, data);
	return (ft_remove_quotes(result));
}

void	ft_expand(t_data *data)
{
	int			i;
	bool		quotes;
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		i = 0;
		quotes = false;
		while (tmp->command && tmp->command[i])
			ft_process_command_arg(data, tmp, &i, &quotes);
		tmp = tmp->next;
	}
}

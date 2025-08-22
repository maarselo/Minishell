/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:20:11 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 15:33:45 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_expansion(char *result, char *str, int *i, int exit_status)
{
	char	*tmp;

	if (str[*i] == '$')
	{
		tmp = ft_expand_var(str, i, exit_status);
		result = ft_join_str_var(result, tmp);
		free(tmp);
	}
	else
	{
		result = ft_join_char_var(result, str[*i]);
		(*i)++;
	}
	return (result);
}

char	*ft_expand_tilde(char *result)
{
	char	*tmp;

	tmp = getenv("HOME");
	if (!tmp)
		return (ft_strdup(result));
	result = ft_join_str_var(result, tmp + 1);
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
	return (joined);
}

char	*ft_join_str_var(char *str, char *to_append)
{
	char	*joined;

	joined = ft_strjoin(str, to_append);
	free(str);
	return (joined);
}

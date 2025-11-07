/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_variables2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:19:54 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/05 18:50:10 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_all_asnum(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '\"' && !ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

int	ft_strlen_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_contains_metachar_var_name(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_var_name(str);
	while (str[i] && i < len - 1)
	{
		if (ft_strchr("@#!$%^*-():;?/.,~+", str[i]))
			return (1);
		i++;
	}
	if (ft_strchr("@#!$%^*-():;?/.,~", str[i]))
		return (1);
	return (0);
}

char	*ft_split_name_var(char *str, t_data *data)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '+')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	name = ft_strndup(str, i);
	if (!name)
		return (ft_perror_free_data_exit(data, T_GENERAL_ERROR), NULL);
	return (name);
}

char	*ft_split_value_var(char *str, t_data *data, char *var_name)
{
	int		index;
	int		start;
	int		len;
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
	if (!value)
		return (free(var_name),
			ft_perror_free_data_exit(data, T_GENERAL_ERROR), NULL);
	return (value);
}

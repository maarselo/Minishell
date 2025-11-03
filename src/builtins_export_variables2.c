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

char	*ft_split_name_var(char *str, t_data *data)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i])
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

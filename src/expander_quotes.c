/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:57:18 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/11 21:13:00 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_quotes(char *str)
{
	int		i;
	bool	in_quotes;
	bool	in_squotes;
	char	*result;

	result = ft_strdup("");
	in_quotes = false;
	in_squotes = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_quotes == false)
			in_squotes = !in_squotes;
		else if (str[i] == '"' && in_squotes == false)
			in_quotes = !in_quotes;
		else
		{
			result = ft_join_char_var(result, str[i]);
			if (!result)
				return (free(str), NULL);
		}
		i++;
	}
	free(str);
	return (result);
}

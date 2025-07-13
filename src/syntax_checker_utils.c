/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:24:52 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/06/30 18:55:47 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	ft_check_content_quotes(char *input)
{
	int		i;
	char	delimiter_type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			delimiter_type = input[i];
			i++;
			while (input[i] && input[i] != delimiter_type)
				i++;
			if (input[i] != delimiter_type)
				return (1);
		}
		i++;
	}
	return (0);
}

//int	ft_count_command(t_token *token_list)
//{
//	int	count;
//
//	count = 1;
//	while (token_list)
//	{
//		if (token_list->type == 1)
//			count++;
//		token_list = token_list->next;
//	}
//	return (count);
//}
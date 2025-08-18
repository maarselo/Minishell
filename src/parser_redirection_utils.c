/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:22:57 by mvillavi          #+#    #+#             */
/*   Updated: 2025/08/18 14:01:24 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_have_any_redirection(t_token *start, t_token *end)
{
	t_token	*tmp;

	tmp = start;

	while (tmp && tmp != end)
	{
		if (ft_get_if_its_redirection_type(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:23:02 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/08/22 20:06:37 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_get_previous_command(t_command *find, t_command *command_list)
{
	t_command	*tmp;
	t_command	*previous;

	if (find == command_list)
		return (NULL);
	previous = command_list;
	tmp = command_list->next;
	while (tmp)
	{
		if (tmp == find)
			return (previous);
		previous = tmp;
		tmp = tmp->next;
	}
	return (tmp);
}

bool	ft_is_last_command(t_command *command)
{
	t_command	*tmp;

	tmp = command;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp == command)
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:00:12 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/16 15:00:12 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextnode;

	if (!lst)
		return ;
	while (*lst)
	{
		nextnode = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = nextnode;
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:40:30 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/10 18:52:03 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <string.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del || !lst)
		return ;
	del(lst->content);
	free(lst);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*next;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = next;
	}
	*lst = NULL;
}
/*
void	ft_free(void *n)
{
	free(n);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_nodo;

	new_nodo = (t_list *)malloc(sizeof(t_list));
	if (!new_nodo)
		return (NULL);
	new_nodo->content = content;
	new_nodo->next = NULL;
	return (new_nodo);
}

int	main(void)
{
	t_list	*ptr1 = ft_lstnew(strdup("Hola"));	
	t_list	*ptr2 = ft_lstnew(strdup(" como"));	
	t_list	*ptr3 = ft_lstnew(strdup(" estas"));	
	t_list	*ptr4 = ft_lstnew(strdup(" puto"));	
	t_list	*ptr5 = ft_lstnew(strdup(" guarro."));
	ptr1->next = ptr2;
	ptr2->next = ptr3;
	ptr3->next = ptr4;
	ptr4->next = ptr5;
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s", (char *)tmp->content);
	ptr2->next = NULL;
	ft_lstclear(&ptr3, ft_free);
	putchar('\n');
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s", (char *)tmp->content);
	ft_free(ptr1->content);
	ft_free(ptr2->content);
	free(ptr1);
	free(ptr2);
	return 0;
}*/

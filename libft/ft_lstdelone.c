/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:08:37 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/10 20:05:53 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta funcion de igual manera ha de unirlo los enlaces aunque libera 
 * solo memoria dinamica que este hecha con malloc, no estatica:arrays. */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
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
	t_list	*ptr1 = ft_lstnew(strdup("Hola "));
	t_list	*ptr2 = ft_lstnew(strdup(" como"));
	t_list	*ptr3 = ft_lstnew(strdup(" estas."));
	ptr1->next = ptr2;
	ptr2->next = ptr3;
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s", (char*)tmp->content);
	ptr1->next = ptr2->next;
	ft_lstdelone(ptr2, ft_free);	
	putchar('\n');
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s", (char*)tmp->content);
	return 0;
}*/

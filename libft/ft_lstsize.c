/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:10:17 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/09 18:20:23 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		count;

	if (!lst)
		return (0);
	tmp = lst;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
/*
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_list  *ft_lstnew(void *content)
{
        t_list  *new_nodo;

        new_nodo = (t_list *)malloc(sizeof(t_list));
        if (!new_nodo)
                return (NULL);
        new_nodo->content = content;
        new_nodo->next = NULL;
        return (new_nodo);
}

int	main(void)
{
	t_list	*ptr1 = ft_lstnew("Hola");
	printf("%s\n", (char *)ptr1->content);
	t_list	*ptr2 = ft_lstnew("Caca");
	ptr1->next = ptr2;
	ptr2->next =NULL;
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s\n", (char *)tmp->content);
	t_list	*ptr3 = ft_lstnew("Pis");
	ft_lstadd_front(&ptr1, ptr3);
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s\n", (char *)tmp->content);
	printf("%d\n", ft_lstsize(ptr3));
	return 0;
}*/

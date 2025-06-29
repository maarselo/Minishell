/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:18:09 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/09 19:47:14 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->next = NULL;
}
/*
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_list	*ft_lstadd(void *content)
{
	if (!content)
		return (NULL);
	t_list	*new_nodo = (t_list *)malloc(sizeof(t_list));
	if (!new_nodo)
		return (NULL);
	new_nodo->content = content;
	new_nodo->next = NULL;
	return (new_nodo);
}

int	main(void)
{
	t_list	*ptr1 = ft_lstadd("hola, ");
	t_list	*ptr2 = ft_lstadd("adios");
	t_list	*ptr3 = ft_lstadd(" mundo.");
	ptr1->next = ptr2;
	ptr2->next = ptr3;
	ptr3->next = NULL;
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s", (char*)tmp->content);
	t_list	*tmp = ft_lstlast(ptr1);
	printf("\n%s\n\n", (char *)tmp->content);

	t_list *ptr4 = ft_lstadd(" Marcelo");
	//for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
	//	printf("%s", (char*)tmp->content);
	//putchar('\n');
	ft_lstadd_back(&ptr1, ptr4);
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s", (char*)tmp->content);
	
	return 0;
}

int main(void)
{
	t_list	*ptr1 = NULL;
	t_list	*ptr2 = ft_lstadd("Hola");
	ft_lstadd_back(&ptr1, ptr2);
	for (t_list *tmp = ptr1; tmp; tmp = tmp->next)
		printf("%s", (char *)tmp->content);
}*/

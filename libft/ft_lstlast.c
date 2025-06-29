/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:20:48 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/09 19:17:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
//#include <stdlib.h>

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
/*
 *while (tmp) Esta forma es hasta que apunte a Nulo y lo convierta
 en nulo y la de arriba si lo QUE SIGUIENTE QUE APUNTA ES NULO sal 
 y devuelve
{
	tmp = tmp->next;
	if (tmp->next == NULL)
		return (tmp
}
 *
 *
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
	printf("\n%s", (char *)tmp->content);
	return 0;
}*/

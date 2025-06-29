/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:54:20 by mvillavi          #+#    #+#             */
/*   Updated: 2025/01/10 23:14:05 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
#include "libft.h"

//t_list *ft_lstnew(void *content);
//t_list *ft_lstlast(t_list *lst);
//void ft_lstadd_back(t_list **lst, t_list *new);
//void ft_lstdelone(t_list *lst, void (*del)(void*));
//void ft_lstclear(t_list **lst, void (*del)(void*));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*tmp;
	t_list	*start;
	t_list	*nodo;

	if (!lst || !f)
		return (NULL);
	tmp = lst;
	start = NULL;
	while (tmp)
	{
		nodo = ft_lstnew(f(tmp->content));
		if (!nodo)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, nodo);
		tmp = tmp->next;
	}
	return (start);
}
/*
void	ft_free(void *content)
{
	free(content);
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

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

void *ft_ft(void *content)
{
    char *ptr = strdup((char *)content); // Crea una copia
    if (!ptr)
        return (NULL);
    int i = 0;
    while (ptr[i])
    {
        ptr[i] = toupper(ptr[i]); // Modifica solo la copia
        i++;
    }
    return (ptr); // Devuelve la copia
}
void    *ft_ft(void *content)
{
    char    *ptr = (char*)content;
    int     i = 0;

    while (ptr[i]) {
        ptr[i] = toupper((char)ptr[i]); // Convierte cada carácter a mayúsculas
        i++;
    }

    return (content); // Retorna el mismo puntero modificado
}

int	main(void)
{
	t_list	*ptr1 = ft_lstnew(strdup("hola"));
	t_list	*ptr2 = ft_lstnew(strdup("como"));
	t_list	*ptr3 = ft_lstnew(strdup("estas"));
	t_list	*ptr4 = ft_lstnew(strdup("guarro"));
	ptr1->next = ptr2;
	ptr2->next = ptr3;
	ptr3->next = ptr4;
	for (t_list *tmp = ptr1; tmp; tmp=tmp->next)
		printf("%s", (char*)tmp->content);
	t_list *vagina= ft_lstmap(ptr1, ft_ft, ft_free);
	putchar('\n');
	for (t_list *tmp = ptr1; tmp; tmp=tmp->next)
		printf("%s", (char*)tmp->content);
	putchar('\n');
	for (t_list *tmp = vagina; tmp; tmp=tmp->next)
		printf("%s", (char*)tmp->content);

	return 0;	
}*/

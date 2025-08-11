/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:57:46 by mvillavi          #+#    #+#             */
/*   Updated: 2025/07/30 23:59:43 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free_token_and_input(char *input, t_token *token_list)
{
    t_token    *current;
    t_token    *next;

    if (input)
        free(input);
    current = token_list;
    while (current != NULL)
    {
        next = current->next;
        if (current->content)
            free(current->content);
        free(current);
        current = next;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:14:03 by mvillavi          #+#    #+#             */
/*   Updated: 2024/12/30 21:14:06 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Los valores como char o int, pueden ser tomados como ASCII.

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

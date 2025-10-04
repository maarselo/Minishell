/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contains_metachar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:08:15 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/04 16:36:07 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_contains_metachar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("@#!$%^*-():;?/.,~+", str[i]))
			return (1);
		i++;
	}
	return (0);
}

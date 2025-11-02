/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 03:22:19 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/05 03:22:19 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (0);
	return (1);
}

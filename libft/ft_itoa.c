/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:55:55 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/15 14:55:55 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_getlen(int n)
{
	size_t	len;
	long	tmp;

	len = 0;
	tmp = n;
	if (tmp <= 0)
		len++;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	return (len);
}

void	ft_getnum(long tmp, size_t len, char *num)
{
	while (tmp)
	{
		num[len - 1] = (tmp % 10) + '0';
		tmp /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	int		sign;
	size_t	len;
	char	*num;
	long	tmp;

	sign = 1;
	tmp = n;
	len = ft_getlen(n);
	if (n < 0)
	{
		tmp *= -1;
		sign = -1;
	}
	num = malloc((len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (tmp == 0)
		num[len - 1] = '0';
	else
		ft_getnum(tmp, len, num);
	if (sign < 0)
		num[0] = '-';
	return (num);
}

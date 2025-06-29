/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:59:05 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/24 19:59:05 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_fd(unsigned long nbr, int fd, int *count, char *base)
{
	unsigned long	baselen;

	baselen = ft_strlen(base);
	if (nbr >= baselen)
	{
		ft_puthex_fd((nbr / baselen), fd, count, base);
		ft_putchar_p(base[nbr % baselen], fd, count);
	}
	else
	{
		ft_putchar_p(base[nbr], fd, count);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:21:12 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/24 19:21:12 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_fd(void *ptr, int fd, int *count)
{
	if (!ptr)
	{
		ft_putstr_p("(nil)", fd, count);
		return ;
	}
	ft_putstr_p("0x", fd, count);
	ft_puthex_fd((unsigned long)ptr, fd, count, HEX_LOW_BASE);
}

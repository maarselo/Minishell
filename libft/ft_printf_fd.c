/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:04:58 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/23 19:04:58 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_fd(int fd, char type, va_list args, int *count)
{
	if (type == 'c')
		ft_putchar_p(va_arg(args, int), fd, count);
	else if (type == 's')
		ft_putstr_p(va_arg(args, char *), fd, count);
	else if (type == 'd' || type == 'i')
		ft_putnbr_p(va_arg(args, int), fd, count);
	else if (type == 'u')
		ft_putnbru_fd(va_arg(args, unsigned int), fd, count);
	else if (type == 'p')
		ft_putptr_fd(va_arg(args, void *), fd, count);
	else if (type == 'x')
		ft_puthex_fd(va_arg(args, unsigned int), fd, count, HEX_LOW_BASE);
	else if (type == 'X')
		ft_puthex_fd(va_arg(args, unsigned int), fd, count, HEX_UPP_BASE);
}

int	ft_printf_fd(int fd, char const *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == '%')
				ft_putchar_p('%', 1, &count);
			ft_format_fd(fd, *str, args, &count);
		}
		else
			ft_putchar_p(*str, fd, &count);
		str++;
	}
	va_end(args);
	return (count);
}

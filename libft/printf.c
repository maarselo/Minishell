/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:05:11 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/29 14:05:13 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_format(char const *s, va_list va, int *count)
{
	if (*s == '%')
		ft_putchar_pf('%', count);
	else if (*s == 'c')
		ft_putchar_pf(va_arg(va, int), count);
	else if (*s == 's')
		ft_putstr_pf(va_arg(va, char *), count);
	else if (*s == 'd' || *s == 'i')
		ft_putnbr_pf((long)va_arg(va, int), "0123456789", count);
	else if (*s == 'u')
		ft_putnbr_pf(va_arg(va, unsigned int), "0123456789", count);
	else if (*s == 'X' || *s == 'x')
	{
		if (*s == 'X')
			ft_putnbr_pf(va_arg(va, unsigned int), "0123456789ABCDEF", count);
		else
			ft_putnbr_pf(va_arg(va, unsigned int), "0123456789abcdef", count);
	}
	else if (*s == 'p')
		ft_putptr_pf(va_arg(va, void *), count);
}

int	ft_printf(char const *s, ...)
{
	va_list	va;
	int		count;

	if (!s)
		return (0);
	va_start(va, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
			ft_format(++s, va, &count);
		else
			ft_putchar_pf(*s, &count);
		s++;
	}
	va_end(va);
	return (count);
}

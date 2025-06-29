/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:08:37 by mvillavi          #+#    #+#             */
/*   Updated: 2025/06/29 14:08:38 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_pf(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putstr_pf(char *s, int *count)
{
	if (!s)
	{
		ft_putstr_pf("(null)", count);
		return ;
	}
	while (*s)
		ft_putchar_pf(*s++, count);
}

void	ft_putnbr_pf(long num, char *base, int *count)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (base_len == 10 && num < 0)
	{
		ft_putchar_pf('-', count);
		num *= -1;
	}
	if (num >= base_len)
		ft_putnbr_pf(num / base_len, base, count);
	ft_putchar_pf(base[num % base_len], count);
}

void	ft_putnbr_ulbase_pf(unsigned long num, char *base, int *count)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (num >= (unsigned long)base_len)
		ft_putnbr_pf(num / (unsigned long)base_len, base, count);
	ft_putchar_pf(base[num % base_len], count);
}

void	ft_putptr_pf(void *ptr, int *count)
{
	if (!ptr)
	{
		ft_putstr_pf("(nil)", count);
		return ;
	}
	ft_putstr_pf("0x", count);
	ft_putnbr_ulbase_pf((unsigned long)ptr, "0123456789abcdef", count);
}

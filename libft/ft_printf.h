/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:05:23 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/01/23 19:05:23 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int			ft_printf(char const *str, ...);
int			ft_printf_fd(int fd, char const *str, ...);
void		ft_format(char type, va_list args, int *count);
void		ft_putchar_p(char c, int fd, int *count);
void		ft_putstr_p(char *s, int fd, int *count);
void		ft_putnbr_p(int n, int fd, int *count);
void		ft_putnbru_fd(unsigned int n, int fd, int *count);
void		ft_putptr_fd(void *ptr, int fd, int *count);
void		ft_puthex_fd(unsigned long nbr, int fd, int *count, char *base);

#endif
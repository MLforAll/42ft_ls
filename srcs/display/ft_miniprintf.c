/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_miniprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 01:44:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 05:35:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_ls.h"

static void	print_arg(char conv, va_list vlst)
{
	if (conv == 'c')
		ft_putchar(va_arg(vlst, int));
	else if (conv == 'd' || conv == 'i')
		ft_putnbr(va_arg(vlst, int));
	else if (conv == 'l')
		ft_putnbr_longlong(va_arg(vlst, long long));
	else if (conv == 's')
		ft_putstr(va_arg(vlst, char*));
}

void		ft_miniprintf(char *format, ...)
{
	va_list		vlst;

	va_start(vlst, format);
	while (*format)
	{
		if (*format == '%')
		{
			print_arg(*(format + 1), vlst);
			format++;
		}
		else
			ft_putchar(*format);
		format++;
	}
	va_end(vlst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 01:44:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/05 15:38:21 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_ls.h"

#include <stdio.h>

static void	print_arg(char **fmt, va_list vlst)
{
	size_t		width;
	int			justf;

	width = 0;
	justf = 0;
	while (*fmt && !ft_isalpha(**fmt))
	{
		*fmt += 1;
		if (**fmt == '$')
			width = va_arg(vlst, size_t);
		else if (**fmt == '-')
			justf = 1;
		else if (**fmt == 'c')
			print_char_width(va_arg(vlst, int), width, justf);
		else if (**fmt == 'd' || **fmt == 'i')
			print_int_width(va_arg(vlst, int), width, justf);
		else if (**fmt == 'l')
			print_ll_width(va_arg(vlst, long long), width, justf);
		else if (**fmt == 's')
			print_str_width(va_arg(vlst, char*), width, justf);
		else
			ft_putstr(*fmt);
	}
}

void		ft_lsprint(char *format, ...)
{
	va_list		vlst;

	va_start(vlst, format);
	while (*format)
	{
		if (*format == '%')
			print_arg(&format, vlst);
		else
			ft_putchar(*format);
		format++;
	}
	va_end(vlst);
}

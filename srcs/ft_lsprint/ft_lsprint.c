/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 01:44:07 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 17:57:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_lsprint.h"

/*
** FT_LSPRINT PARSER
*/

static void	print_arg(int fd, char **fmt, va_list vlst)
{
	t_opts		opts;
	size_t		*ptr;

	ft_bzero(&opts, sizeof(t_opts));
	ptr = &opts.width;
	while (**fmt && !ft_isalpha(**fmt))
	{
		(*fmt)++;
		if (**fmt == '$')
			*ptr = va_arg(vlst, size_t);
		else if (**fmt == '.')
			ptr = &opts.max;
		else if (ft_isdigit(**fmt))
			*ptr = *ptr * 10 + **fmt - '0';
		else if (**fmt == '-')
			opts.justf = 1;
		else if (**fmt == 'c')
			print_char_width_fd(fd, va_arg(vlst, int), opts);
		else if (**fmt == 'd' || **fmt == 'i')
			print_int_width_fd(fd, va_arg(vlst, int), opts);
		else if (**fmt == 'l')
			print_ll_width_fd(fd, va_arg(vlst, long long), opts);
		else if (**fmt == 's')
			print_str_width_fd(fd, va_arg(vlst, char*), opts);
	}
}

static void	ft_lsprint_core(int fd, char *fmt, va_list vlst)
{
	while (*fmt)
	{
		if (*fmt == '%')
			print_arg(fd, &fmt, vlst);
		else
			ft_putchar_fd(*fmt, fd);
		fmt++;
	}
}

void		ft_lsprint_fd(int fd, char *format, ...)
{
	va_list		vlst;

	va_start(vlst, format);
	ft_lsprint_core(fd, format, vlst);
	va_end(vlst);
}

void		ft_lsprint(char *format, ...)
{
	va_list		vlst;

	va_start(vlst, format);
	ft_lsprint_core(1, format, vlst);
	va_end(vlst);
}

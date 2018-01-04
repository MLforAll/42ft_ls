/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 00:46:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 02:55:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "ft_ls.h"

static void	print_spaces_for_width(size_t len, size_t width)
{
	size_t	n;

	n = (len < width) ? width - len : 0;
	while (n--)
		ft_putchar(' ');
}

void		print_int_width(int n, size_t width)
{
	print_spaces_for_width(ft_nbrlen((long long)n), width);
	ft_putnbr(n);
}

void		print_offt_width(off_t size, size_t width)
{
	print_spaces_for_width(ft_nbrlen(size), width);
	ft_putnbr_longlong(size);
}

void		print_str_width(char *s, size_t width)
{
	print_spaces_for_width(s != NULL ? ft_strlen(s) : 6, width);
	ft_putstr(s != NULL ? s : "(null)");
}

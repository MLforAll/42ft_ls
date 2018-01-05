/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 00:46:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/05 15:35:48 by kdumarai         ###   ########.fr       */
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

void		print_int_width(int n, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width(ft_nbrlen((long long)n), width);
	ft_putnbr(n);
	if (justify)
		print_spaces_for_width(ft_nbrlen((long long)n), width);
}

void		print_ll_width(long long size, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width(ft_nbrlen(size), width);
	ft_putnbr_ll(size);
	if (justify)
		print_spaces_for_width(ft_nbrlen(size), width);
}

void		print_str_width(char *s, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width(s != NULL ? ft_strlen(s) : 6, width);
	ft_putstr(s != NULL ? s : "(null)");
	if (justify)
		print_spaces_for_width(s != NULL ? ft_strlen(s) : 6, width);
}

void		print_char_width(char c, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width(1, width);
	ft_putchar(c);
	if (justify)
		print_spaces_for_width(1, width);
}

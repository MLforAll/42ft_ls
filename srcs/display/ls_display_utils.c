/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 00:46:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/09 17:22:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "ft_ls.h"

static void	print_spaces_for_width_fd(int fd, size_t len, size_t width)
{
	size_t	n;

	n = (len < width) ? width - len : 0;
	while (n--)
		ft_putchar_fd(' ', fd);
}

void		print_int_width_fd(int fd, int n, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width_fd(fd, ft_nbrlen((long long)n), width);
	ft_putnbr_fd(n, fd);
	if (justify)
		print_spaces_for_width_fd(fd, ft_nbrlen((long long)n), width);
}

void		print_ll_width_fd(int fd, long long size, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width_fd(fd, ft_nbrlen(size), width);
	ft_putnbr_ll_fd(size, fd);
	if (justify)
		print_spaces_for_width_fd(fd, ft_nbrlen(size), width);
}

void		print_str_width_fd(int fd, char *s, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width_fd(fd, s != NULL ? ft_strlen(s) : 6, width);
	ft_putstr_fd(s != NULL ? s : "(null)", fd);
	if (justify)
		print_spaces_for_width_fd(fd, s != NULL ? ft_strlen(s) : 6, width);
}

void		print_char_width_fd(int fd, char c, size_t width, int justify)
{
	if (!justify)
		print_spaces_for_width_fd(fd, 1, width);
	ft_putchar_fd(c, fd);
	if (justify)
		print_spaces_for_width_fd(fd, 1, width);
}

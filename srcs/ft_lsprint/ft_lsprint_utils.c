/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsprint_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 00:46:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/13 19:24:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "libft.h"
#include "ft_lsprint.h"

/*
** THIS FILE REFS FUNCTIONS USED BY FT_LSPRINT
*/

/*
** NOTE FROM 10/01/18:
**	Only print_str_with_fd cares about 'max'
*/

void	print_nspaces_fd(int fd, size_t len, size_t width)
{
	size_t	n;

	n = (len < width) ? width - len : 0;
	while (n--)
		ft_putchar_fd(' ', fd);
}

void	print_int_width_fd(int fd, int n, t_opts opts)
{
	if (!opts.justf)
		print_nspaces_fd(fd, ft_nbrlen((long long)n), opts.width);
	ft_putnbr_fd(n, fd);
	if (opts.justf)
		print_nspaces_fd(fd, ft_nbrlen((long long)n), opts.width);
}

void	print_ll_width_fd(int fd, long long n, t_opts opts)
{
	if (!opts.justf)
		print_nspaces_fd(fd, ft_nbrlen(n), opts.width);
	ft_putnbr_ll_fd(n, fd);
	if (opts.justf)
		print_nspaces_fd(fd, ft_nbrlen(n), opts.width);
}

void	print_str_width_fd(int fd, char *s, t_opts opts)
{
	size_t	slen;

	slen = (s != NULL) ? ft_strlen(s) : 6;
	if (!opts.justf)
		print_nspaces_fd(fd, slen, opts.width);
	write(fd, s != NULL ? s : "(null)", opts.max == 0 ? slen : opts.max);
	if (opts.justf)
		print_nspaces_fd(fd, slen, opts.width);
}

void	print_char_width_fd(int fd, char c, t_opts opts)
{
	if (!opts.justf)
		print_nspaces_fd(fd, 1, opts.width);
	ft_putchar_fd(c, fd);
	if (opts.justf)
		print_nspaces_fd(fd, 1, opts.width);
}

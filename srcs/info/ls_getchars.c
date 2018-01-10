/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getchars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:06:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 18:28:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"

char		get_ifmt_char(mode_t st_mode, int bigf)
{
	if ((st_mode & S_IFMT) == S_IFDIR)
		return (bigf ? '/' : 'd');
	if ((st_mode & S_IFMT) == S_IFLNK)
		return (bigf ? '@' : 'l');
	if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((st_mode & S_IFMT) == S_IFIFO)
		return (bigf ? '|' : 'p');
	if ((st_mode & S_IFMT) == S_IFSOCK)
		return (bigf ? '=' : 's');
	if ((st_mode & S_IFMT) == S_IFWHT)
		return (bigf ? '%' : 'w');
	if (bigf && ((st_mode & 64) || (st_mode & 8) || (st_mode & 1)))
		return ('*');
	return (!bigf ? '-' : '\0');
}

char		get_perm_char(mode_t fmode, mode_t mask)
{
	char		pchr;

	if (mask == 256 || mask == 32 || mask == 4)
		pchr = 'r';
	else if (mask == 128 || mask == 16 || mask == 2)
		pchr = 'w';
	else if (mask == 64 || mask == 8 || mask == 1)
	{
		if ((mask == 64 && (fmode & S_ISUID) != 0)
			|| (mask == 8 && (fmode & S_ISGID) != 0))
			pchr = 's';
		else if (mask == 1 && (fmode & S_ISVTX) != 0)
			pchr = 't';
		else
			pchr = 'x';
	}
	else
		return ('-');
	if ((fmode & mask) != 0)
		return (pchr);
	return (pchr == 's' || pchr == 't' ? ft_toupper(pchr) : '-');
}

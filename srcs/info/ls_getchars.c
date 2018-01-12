/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getchars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:06:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/12 17:33:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"

char		get_ifmt_char(mode_t mode, int bigf)
{
	if ((mode & S_IFMT) == S_IFDIR)
		return (bigf ? '/' : 'd');
	if ((mode & S_IFMT) == S_IFLNK)
		return (bigf ? '@' : 'l');
	if ((mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((mode & S_IFMT) == S_IFIFO)
		return (bigf ? '|' : 'p');
	if ((mode & S_IFMT) == S_IFSOCK)
		return (bigf ? '=' : 's');
	if ((mode & S_IFMT) == S_IFWHT)
		return (bigf ? '%' : 'w');
	if (bigf && ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH)))
		return ('*');
	return (!bigf ? '-' : '\0');
}

char		get_perm_char(mode_t fmode, mode_t mask)
{
	char		pchr;

	if (mask == S_IRUSR || mask == S_IRGRP || mask == S_IROTH)
		pchr = 'r';
	else if (mask == S_IWUSR || mask == S_IWGRP || mask == S_IWOTH)
		pchr = 'w';
	else if (mask == S_IXUSR || mask == S_IXGRP || mask == S_IXOTH)
	{
		if ((mask == S_IXUSR && (fmode & S_ISUID))
			|| (mask == S_IXGRP && (fmode & S_ISGID)))
			pchr = 's';
		else if (mask == S_IXOTH && (fmode & S_ISVTX))
			pchr = 't';
		else
			pchr = 'x';
	}
	else
		return ('-');
	if ((fmode & mask))
		return (pchr);
	return (pchr == 's' || pchr == 't' ? ft_toupper(pchr) : '-');
}

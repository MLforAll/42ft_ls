/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getchars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:06:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/17 21:13:14 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include "libft.h"
#include "ls_data.h"

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

char		get_perm_char(mode_t mode, mode_t mask)
{
	char		pchr;

	if (mask == S_IRUSR || mask == S_IRGRP || mask == S_IROTH)
		pchr = 'r';
	else if (mask == S_IWUSR || mask == S_IWGRP || mask == S_IWOTH)
		pchr = 'w';
	else if (mask == S_IXUSR || mask == S_IXGRP || mask == S_IXOTH)
	{
		if ((mask == S_IXUSR && (mode & S_ISUID))
			|| (mask == S_IXGRP && (mode & S_ISGID)))
			pchr = 's';
		else if (mask == S_IXOTH && (mode & S_ISVTX))
			pchr = 't';
		else
			pchr = 'x';
	}
	else
		return ('-');
	if ((mode & mask))
		return (pchr);
	return (pchr == 's' || pchr == 't' ? ft_toupper(pchr) : '-');
}

char		get_acl_xattrs_char(t_elem *elem)
{
	char		ret;
	acl_t		acl;
	acl_entry_t	dummy;
	int			aclg_ret;

	ret = ' ';
	acl = acl_get_link_np(elem->fpath, ACL_TYPE_EXTENDED);
	aclg_ret = acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy);
	if (acl && aclg_ret == 0)
		ret = '+';
	else if (aclg_ret == -1)
		acl_free((void*)acl);
	if (elem->xattrs)
		ret = '@';
	return (ret);
}

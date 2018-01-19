/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getchars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:06:34 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/19 05:28:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include "libft.h"
#include "ls_data.h"

char		get_ifmt_char(mode_t mode, int bigf)
{
	if (S_ISDIR(mode))
		return (bigf ? '/' : 'd');
	if (S_ISLNK(mode))
		return (bigf ? '@' : 'l');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISFIFO(mode))
		return (bigf ? '|' : 'p');
	if (S_ISSOCK(mode))
		return (bigf ? '=' : 's');
	if (S_ISWHT(mode))
		return (bigf ? '%' : 'w');
	if (bigf && ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH)))
		return ('*');
	return (!bigf ? '-' : 0);
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
	if (acl)
		acl_free((void*)acl);
	if (elem->xattrs)
		ret = '@';
	return (ret);
}

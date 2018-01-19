/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/19 18:49:44 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <time.h>
#include <unistd.h>
#include "ft_ls.h"

static void		print_elem_date(t_stat *st)
{
	time_t			time_n;
	time_t			time_now;
	time_t			time_diff;
	size_t			tillnl;
	char			*time_str;

	time_n = st->st_mtime;
	time_str = ctime(&time_n);
	time_now = time(NULL);
	time_diff = (time_now >= time_n) ? time_now - time_n : 0;
	ft_putchar(' ');
	if (time_n > time_now || time_diff >= HALFYRSEC)
	{
		ft_lsprint("%.6s  ", time_str + 4);
		tillnl = 0;
		time_str += 20;
		while (!ft_isdigit(*time_str))
			time_str++;
		while (*(time_str + tillnl) != '\n')
			tillnl++;
		write(1, time_str, tillnl);
	}
	else
		ft_lsprint("%.12s", time_str + 4);
	ft_putchar(' ');
}

static void		print_xattrs(t_elem *elem)
{
	char		*ptr;
	ssize_t		size;
	ssize_t		offset;
	size_t		len;

	if (!optexists(A_LOPT) || !optexists(A_ATOPT))
		return ;
	ptr = elem->xattrs;
	offset = 0;
	while (offset < elem->lxattr)
	{
		size = getxattr(elem->fpath, ptr, NULL, 0, 0, XATTR_NOFOLLOW);
		ft_lsprint("\n\t%s\t", ptr);
		if (optexists(A_HOPT))
			print_human_fmt(size);
		else
			ft_lsprint("%3i", size);
		ft_putchar(' ');
		len = ft_strlen(ptr);
		offset += len + 1;
		ptr += len + 1;
	}
}

static size_t	print_elem_name(t_elem *elem)
{
	size_t			ret;
	int				pclr_ret;
	char			getc_ret;

	ret = 0;
	pclr_ret = print_clr(elem->st.st_mode);
	if (elem->fname)
		ret = ft_strlen(elem->fname);
	if (ret != 0)
		write(1, elem->fname, ret);
	if (pclr_ret)
		ft_putstr("\033[0;39m");
	if (optexists(A_FFOPT))
	{
		if ((getc_ret = get_ifmt_char(elem->st.st_mode, 1)))
			ft_putchar(getc_ret);
		ret += (getc_ret != 0);
	}
	if (elem->sympath && optexists(A_LOPT))
		ft_lsprint(" -> %s", elem->sympath);
	return (ret);
}

static size_t	print_elem_props(t_elem *elem, t_group *grp)
{
	size_t			ret;
	mode_t			getp;

	if (optexists(A_SOPT))
		ft_lsprint("%$i ", grp->maxlens[0], elem->st.st_blocks);
	if (optexists(A_LOPT))
	{
		ft_putchar(get_ifmt_char(elem->st.st_mode, 0));
		getp = S_IRUSR * 2;
		while (getp /= 2)
			ft_putchar(get_perm_char(elem->st.st_mode, getp));
		ft_lsprint("%c %$i %$-s  %$-s  ", get_acl_xattrs_char(elem), \
			grp->maxlens[1], elem->st.st_nlink, \
			grp->maxlens[2], elem->usrname, \
			grp->maxlens[3], elem->grname);
		print_elem_size(elem, grp);
		print_elem_date(&elem->st);
	}
	ret = print_elem_name(elem);
	print_xattrs(elem);
	return (ret);
}

void			print_elems(t_group *grp)
{
	t_size			nb_cr;
	size_t			spacesn;
	unsigned int	cnts[2];
	t_elem			*elem;
	t_elem			*tmp;

	elem = grp->elems;
	get_ls_columns_rows(&nb_cr, grp);
	cnts[0] = 0;
	while (elem && cnts[0]++ < nb_cr.height)
	{
		cnts[1] = 0;
		tmp = elem;
		while (tmp && cnts[1]++ < nb_cr.width)
		{
			if (tmp != elem)
				print_nspaces_fd(1, 0, spacesn);
			spacesn = get_spaces_to_add(print_elem_props(tmp, grp), grp);
			tmp = ft_elem_nnext(tmp, nb_cr.height);
		}
		elem = elem->next;
		ft_putchar('\n');
	}
}

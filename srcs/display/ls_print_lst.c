/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/06 21:29:49 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <time.h>
#include "ft_ls.h"

static char		get_ifmt_char(mode_t st_mode, int bigf)
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

static char		get_perm_char(mode_t fmode, mode_t mask)
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

static void		print_elem_props(t_fstats *dc, t_queue *queue, int optsb)
{
	char		*mtime_str;
	mode_t		getp;

	mtime_str = ft_strsub(ctime(&dc->mtime), 4, 12);
	if (OPTEXISTS(optsb, A_SOPT))
		ft_lsprint("%$i ", queue->maxlens[0], dc->nbblk);
	if (OPTEXISTS(optsb, A_LOPT))
	{
		ft_putchar(get_ifmt_char(dc->fmode, 0));
		getp = S_IRUSR * 2;
		while (getp /= 2)
			ft_putchar(get_perm_char(dc->fmode, getp));
		ft_lsprint("  %$i %$-s  %$-s  %$l %s ", queue->maxlens[1], dc->nblink, \
			queue->maxlens[2], dc->usrname, queue->maxlens[3], dc->grname, \
			queue->maxlens[4], dc->size, mtime_str);
	}
	ft_putstr(dc->fname);
	if (OPTEXISTS(optsb, A_FFOPT))
		ft_putchar(get_ifmt_char(dc->fmode, 1));
	if (dc->sympath && OPTEXISTS(optsb, A_LOPT))
		ft_lsprint(" -> %s", dc->sympath);
	ft_putchar('\n');
	ft_strdel(&mtime_str);
}

static void		print_elems(t_queue *queue, int optsb, t_list **reclst)
{
	t_fstats	*tmp;
	int			rev;
	t_fstats	*dc;

	dc = queue->dc;
	if (queue->total == -1 || !dc)
		return ;
	rev = OPTEXISTS(optsb, A_ROPT);
	sort_ls(&dc, OPTEXISTS(optsb, A_TOPT) ? &sort_mtime : &sort_alpha, rev);
	if ((OPTEXISTS(optsb, A_LOPT) || OPTEXISTS(optsb, A_SOPT)) && queue->dname)
		ft_lsprint("total %l\n", queue->total);
	*reclst = NULL;
	tmp = dc;
	while (dc)
	{
		print_elem_props(dc, queue, optsb);
		if (OPTEXISTS(optsb, A_RROPT) && get_ifmt_char(dc->fmode, 0) == 'd'
			&& ft_strcmp(dc->fname, ".") && ft_strcmp(dc->fname, ".."))
			ft_lstpushback(reclst, dc->fpath, ft_strlen(dc->fpath) + 1);
		dc = dc->next;
	}
	free_dir_content(&tmp);
}

void			print_dcs(t_queue *dcs, int optsb, int add_nl)
{
	t_queue		*tmp;
	t_list		*reclst;

	reclst = NULL;
	tmp = dcs;
	while (tmp)
	{
		if (tmp != dcs || add_nl)
			ft_putchar('\n');
		if (((dcs->next) || add_nl) && tmp->dname)
			ft_lsprint("%s:\n", tmp->dname);
		print_elems(tmp, optsb, &reclst);
		if (reclst)
		{
			list_dirs(reclst, optsb, 1);
			ft_lstdel(&reclst, &ft_lstdelf);
		}
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 04:37:42 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <time.h>
#include "ft_ls.h"

#include <stdio.h>

/*
** printf is later to be replaced by ft_printf
** or perhaps maybe some putstrs..
*/

static char		get_ifmt_char(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	return ('-');
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
	char		ftype;
	char		*mtime_str;
	mode_t		getp;

	/*if ((optsb & A_AOPT) == 0 && *dc->fname == '.')
		return ;*/
	ftype = get_ifmt_char(dc->fmode);
	mtime_str = ft_strsub(ctime(&dc->mtime), 4, 12);
	if (OPTEXISTS(optsb, A_SOPT))
	{
		print_int_width(dc->nbblk, queue->maxlens[0]);
		ft_putchar(' ');
	}
	if (OPTEXISTS(optsb, A_LOPT))
	{
		ft_putchar(ftype);
		getp = S_IRUSR * 2;
		while (getp /= 2)
			ft_putchar(get_perm_char(dc->fmode, getp));
		ft_putstr("  ");
		print_int_width(dc->nblink, queue->maxlens[1]);
		ft_putchar(' ');
		print_str_width(dc->usrname, queue->maxlens[2]);
		ft_putstr("  ");
		print_str_width(dc->grname, queue->maxlens[3]);
		ft_putstr("  ");
		print_offt_width(dc->size, queue->maxlens[4]);
		ft_putchar(' ');
		ft_putstr(mtime_str);
		ft_putchar(' ');
	}
	ft_putstr(dc->fname);
	if (ftype == 'd' && OPTEXISTS(optsb, A_FOPT))
		ft_putchar('/');
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
	sort_ls(&dc, ((optsb & A_TOPT) != 0) ? &sort_mtime : &sort_alpha, rev);
	if (OPTEXISTS(optsb, A_LOPT) && dclen(dc) > 2)
		printf("total %i\n", queue->total);
	*reclst = NULL;
	tmp = dc;
	while (dc)
	{
		print_elem_props(dc, queue, optsb);
		if ((optsb & A_RROPT) != 0 && get_ifmt_char(dc->fmode) == 'd'
			&& ft_strcmp(dc->fname, ".") && ft_strcmp(dc->fname, "..")
			&& (*dc->fname != '.' || OPTEXISTS(optsb, A_AOPT)))
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
			printf("\n");
		if ((dcs->next) || add_nl)
			printf("%s:\n", tmp->dname);
		print_elems(tmp, optsb, &reclst);
		if (reclst)
		{
			list_dirs(reclst, optsb, 1);
			ft_lstdel(&reclst, &ft_lstdelf);
		}
		tmp = tmp->next;
	}
}

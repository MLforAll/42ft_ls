/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/21 21:59:15 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <time.h>
#include "ft_ls.h"

#include <stdio.h>

/*
** printf is later to be replaced by ft_printf
*/

/*
** Not sure about c and f
*/

static char			get_ifmt_char(mode_t st_mode)
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
		return ('f');
	return ('-');
}

static char			get_perm_char(mode_t fmode, mode_t mask)
{
	char		pchr;

	if (mask == 256 || mask == 32 || mask == 4)
		pchr = 'r';
	else if (mask == 128 || mask == 16 || mask == 2)
		pchr = 'w';
	else if (mask == 64 || mask == 8 || mask == 1)
		pchr = 'x';
	if ((fmode & mask) != 0)
		return (pchr);
	return ('-');
}

static void			print_out(t_fstats *dc, int optsb)
{
	char		ftype;
	char		*mtime_str;
	mode_t		getp;

	if ((optsb & 0x2) == 0 && *dc->fname == '.')
		return ;
	ftype = get_ifmt_char(dc->fmode);
	mtime_str = ft_strsub(ctime(&dc->mtime), 4, 12);
	printf("%c", ftype);
	getp = S_IRUSR;
	while (getp)
	{
		printf("%c", get_perm_char(dc->fmode, getp));
		getp /= 2;
	}
	printf("  %2i %s  %s %6lli %s %s", dc->nblink, \
		dc->usrname, dc->grname, dc->size, mtime_str, dc->fname);
	if (ftype == 'd')
		printf("/");
	printf("\n");
	ft_strdel(&mtime_str);
}

static t_list		*show_directory_files(const char *path, int optsb)
{
	t_list		*reclst;
	t_fstats	*dc;
	t_fstats	*tmp;
	int			total;
	int			rev;

	if ((total = get_dir_content(path, &dc)) == -1)
		return (NULL);
	rev = (optsb & 0x4) != 0;
	sort_ls_lst(&dc, ((optsb & 0x8) != 0) ? &sort_mtime : &sort_alpha, rev);
	printf("total %i\n", total);
	reclst = NULL;
	tmp = dc;
	while (dc)
	{
		print_out(dc, optsb);
		if ((optsb & 0x10) != 0 && get_ifmt_char(dc->fmode) == 'd'
			&& ft_strcmp(dc->fname, ".") && ft_strcmp(dc->fname, "..")
			&& (*dc->fname != '.' || (optsb & 0x2) != 0))
			ft_lstpushback(&reclst, dc->fpath, ft_strlen(dc->fpath) + 1);
		dc = dc->next;
	}
	free_dir_content(&tmp);
	return (reclst);
}

void				list_dirs(t_list **targets, int optsb, int add_nl)
{
	t_list		*tmp;
	t_list		*reclst;
	char		*cts;

	tmp = *targets;
	cts = NULL;
	while (tmp || !cts)
	{
		if (tmp != *targets || add_nl)
			printf("\n");
		if ((tmp && (*targets)->next) || add_nl)
			printf("%s:\n", tmp->content);
		if (!tmp)
			cts = ".";
		else
			cts = tmp->content;
		reclst = show_directory_files(cts, optsb);
		if (reclst)
			list_dirs(&reclst, optsb, 1);
		if (!*targets)
			break ;
		tmp = tmp->next;
	}
	ft_lstdel(targets, &ft_lstdelf);
}

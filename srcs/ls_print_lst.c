/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/20 21:40:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <time.h>
#include "ft_ls.h"

#include <stdio.h>

/*
** printf is later to be replaced by ft_printf
*/

static void			print_out(t_fstats *dc, int optsb)
{
	char	*mtime_str;

	if ((optsb & 0x2) == 0 && *dc->fname == '.')
		return ;
	mtime_str = ft_strsub(ctime(&dc->mtime), 4, 12);
	printf("%c--------- %2i %s %11s %6lli %s %s", dc->ftype, dc->nblink, \
		dc->usrname, dc->grname, dc->size, mtime_str, dc->fname);
	if (dc->ftype == 'd')
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

	if ((total = get_dir_content(path, &dc)) == -1)
		return (NULL);
	if ((optsb & 0x8) != 0)
		sort_ls_lst(&dc, &sort_mtime);
	else
		sort_ls_lst(&dc, &sort_alpha);
	printf("total %i\n", total);
	reclst = NULL;
	tmp = dc;
	while (dc)
	{
		print_out(dc, optsb);
		if ((optsb & 0x10) != 0 && dc->ftype == 'd' && ft_strcmp(dc->fname, ".") && ft_strcmp(dc->fname, ".."))
			ft_lstadd(&reclst, ft_lstnew(dc->fpath, ft_strlen(dc->fpath) + 1));
		dc = dc->next;
	}
	free_dir_content(&tmp);
	return (reclst);
}

void				list_dirs(t_list **targets, int optsb, int add_nl)
{
	t_list			*tmp;
	t_list			*reclst;
	char			*cts;

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
		if (!*targets)
			break ;
		if (reclst)
			list_dirs(&reclst, optsb, 1);
		tmp = tmp->next;
	}
	ft_lstdel(targets, &ft_lstdelf);
}

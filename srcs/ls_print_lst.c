/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/19 21:57:36 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ft_ls.h"

#include <stdio.h>

/*
** printf is later to be replaced by ft_printf
*/

static t_list		*show_directory_files(const char *path, int recursive)
{
	t_list		*reclst;
	t_fstats	*dc;
	t_fstats	*tmp;
	int			total;

	if ((total = get_dir_content(path, &dc)) == -1)
		return (NULL);
	printf("total %i\n", total);
	reclst = NULL;
	tmp = dc;
	while (dc)
	{
		printf("%c--------- %2i %s %11s %6lli %s %s\n", dc->ftype, dc->nblink, dc->usrname, dc->grname, dc->size, dc->timec, dc->fname);
		if (recursive && dc->ftype == 'd' && ft_strcmp(dc->fname, ".") && ft_strcmp(dc->fname, ".."))
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
		reclst = show_directory_files(cts, (optsb & 0x10) != 0);
		if (!*targets)
			break ;
		if (reclst)
			list_dirs(&reclst, optsb, 1);
		tmp = tmp->next;
	}
	ft_lstdel(targets, &ft_lstdelf);
}

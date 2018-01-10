/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 21:25:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <time.h>
#include "ft_ls.h"

static void		print_elem_date(t_stat *st)
{
	time_t	time_n;
	char	*time_str;

	time_n = st->st_mtime;
	time_str = ctime(&time_n);
	ft_putchar(' ');
	if (time(NULL) - time_n >= HALFYRSEC)
		ft_lsprint("%.6s  %.4s", time_str + 4, time_str + 20);
	else
		ft_lsprint("%.12s", time_str + 4);
	ft_putchar(' ');
}

static void		print_elem_name(t_fstats *dc)
{
	int		pclr_ret;

	pclr_ret = print_clr(dc->st.st_mode);
	if (dc->fname)
		ft_putstr(dc->fname);
	if (pclr_ret)
		ft_putstr("\033[0;39m");
	if (OPTEXISTS(A_FFOPT))
		ft_putchar(get_ifmt_char(dc->st.st_mode, 1));
	if (dc->sympath && OPTEXISTS(A_LOPT))
		ft_lsprint(" -> %s", dc->sympath);
}

static void		print_elem_props(t_fstats *dc, t_queue *queue)
{
	mode_t		getp;

	if (OPTEXISTS(A_SOPT))
		ft_lsprint("%$i ", queue->maxlens[0], dc->st.st_nlink);
	if (OPTEXISTS(A_LOPT))
	{
		ft_putchar(get_ifmt_char(dc->st.st_mode, 0));
		getp = S_IRUSR * 2;
		while (getp /= 2)
			ft_putchar(get_perm_char(dc->st.st_mode, getp));
		ft_lsprint("  %$i %$-s  %$-s  ", \
			queue->maxlens[1], dc->st.st_nlink, \
			queue->maxlens[2], dc->usrname, \
			queue->maxlens[3], dc->grname);
		if (S_ISCHR(dc->st.st_mode) || S_ISBLK(dc->st.st_mode))
			ft_lsprint("%3i, %3i", major(dc->st.st_rdev), \
									minor(dc->st.st_rdev));
		else
			ft_lsprint("%$l", queue->maxlens[4], dc->st.st_size);
		print_elem_date(&dc->st);
	}
	print_elem_name(dc);
	ft_putchar('\n');
}

void			print_elems(t_queue *queue, t_list **reclst)
{
	t_fstats	*tmp;
	int			rev;
	t_fstats	*dc;

	dc = queue->dc;
	if (queue->total == -1 || !dc)
		return ;
	rev = OPTEXISTS(A_ROPT);
	sort_ls(&dc, OPTEXISTS(A_TOPT) ? &sort_mtime : &sort_alpha, rev);
	if ((OPTEXISTS(A_LOPT) || OPTEXISTS(A_SOPT)) && queue->dname)
		ft_lsprint("total %l\n", queue->total);
	*reclst = NULL;
	tmp = dc;
	while (dc)
	{
		print_elem_props(dc, queue);
		if (OPTEXISTS(A_RROPT) && S_ISDIR(dc->st.st_mode)
			&& ft_strcmp(dc->fname, ".") && ft_strcmp(dc->fname, ".."))
			ft_lstpushback(reclst, dc->fpath, ft_strlen(dc->fpath) + 1);
		dc = dc->next;
	}
	free_dir_content(&tmp);
}

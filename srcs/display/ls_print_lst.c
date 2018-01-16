/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 22:04:22 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "ft_ls.h"

static void		print_elem_date(t_stat *st)
{
	time_t		time_n;
	time_t		time_now;
	time_t		time_diff;
	char		*time_str;

	time_n = st->st_mtime;
	time_now = time(NULL);
	time_diff = (time_now >= time_n) ? time_now - time_n : time_n - time_now;
	time_str = ctime(&time_n);
	ft_putchar(' ');
	if (time_diff >= HALFYRSEC)
		ft_lsprint("%.6s  %.4s", time_str + 4, time_str + 20);
	else
		ft_lsprint("%.12s", time_str + 4);
	ft_putchar(' ');
}

static size_t	print_elem_name(t_fstats *dc)
{
	size_t		ret;
	int			pclr_ret;
	char		getc_ret;

	ret = 0;
	pclr_ret = print_clr(dc->st.st_mode);
	if (dc->fname)
		ret = ft_strlen(dc->fname);
	if (ret != 0)
		write(1, dc->fname, ret);
	if (pclr_ret)
		ft_putstr("\033[0;39m");
	if (OPTEXISTS(A_FFOPT))
	{
		getc_ret = get_ifmt_char(dc->st.st_mode, 1);
		ft_putchar(getc_ret);
		ret += (getc_ret != 0);
	}
	if (dc->sympath && OPTEXISTS(A_LOPT))
		ft_lsprint(" -> %s", dc->sympath);
	return (ret);
}

static size_t	print_elem_props(t_fstats *dc, t_queue *queue)
{
	mode_t			getp;

	if (OPTEXISTS(A_SOPT))
		ft_lsprint("%$i ", queue->maxlens[0], dc->st.st_blocks);
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
	return (print_elem_name(dc));
}

void		print_elems(t_queue *queue)
{
	t_size			nb_cr;
	size_t			spacesn;
	unsigned int	cnts[2];
	t_fstats		*dc;
	t_fstats		*tmp;

	dc = queue->dc;
	get_ls_columns_rows(&nb_cr, queue);
	cnts[0] = 0;
	while (dc && cnts[0]++ < nb_cr.height)
	{
		cnts[1] = 0;
		tmp = dc;
		while (tmp && cnts[1]++ < nb_cr.width)
		{
			if (tmp != dc)
				print_nspaces_fd(1, 0, spacesn);
			spacesn = get_spaces_to_add(print_elem_props(tmp, queue), queue);
			tmp = ft_dcnnext_elem(tmp, nb_cr.height);
		}
		dc = dc->next;
		ft_putchar('\n');
	}
}

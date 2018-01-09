/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:36:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/09 18:57:30 by kdumarai         ###   ########.fr       */
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

static void		print_element_name(char *name, mode_t mode)
{
	int		pclr_ret;

	pclr_ret = print_clr(mode);
	ft_putstr(name);
	if (pclr_ret)
		ft_putstr("\033[0;39m");
}

static void		print_elem_props(t_fstats *dc, t_queue *queue)
{
	char		*mtime_str;
	mode_t		getp;

	mtime_str = ft_strsub(ctime(&dc->st.st_mtime), 4, 12);
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
			ft_lsprint("%3i, %3i", major(dc->st.st_rdev), minor(dc->st.st_rdev));
		else
			ft_lsprint("%$l", queue->maxlens[4], dc->st.st_size);
		ft_lsprint(" %s ", mtime_str);
	}
	print_element_name(dc->fname, dc->st.st_mode);
	if (OPTEXISTS(A_FFOPT))
		ft_putchar(get_ifmt_char(dc->st.st_mode, 1));
	if (dc->sympath && OPTEXISTS(A_LOPT))
		ft_lsprint(" -> %s", dc->sympath);
	ft_putchar('\n');
	ft_strdel(&mtime_str);
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

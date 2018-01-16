/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 15:15:47 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ls_data.h"
# include "ls_args.h"
# include "ls_lists.h"
# include "ft_lsprint.h"

# define PRGM_NAME	"ft_ls"

/*
** GLOBAL: COLORS
*/

int		g_clrs[12];

/*
** FUNCTIONS: COLORS
*/

void	detect_colors(char *entry);
int		print_clr(mode_t mode);

/*
** ENTRY POINT
*/

int		list_dirs(t_list **paths, int add_nl);

/*
** DB MGMT
*/

t_blkc	get_file_content(t_queue *alst, char *d_name);
t_blkc	get_dir_content(t_queue *alst);
void	free_dir_elem_content(t_fstats **alst);
void	free_dir_content(t_fstats **alst);

/*
** DB Filling
*/

int		fill_fstats(char *d_name, t_fstats *fstats, t_queue *queue);
char	get_ifmt_char(mode_t st_mode, int bigf);
char	get_perm_char(mode_t fmode, mode_t mask);

/*
** DB SORTING
*/

int		sort_alpha(t_fstats *a, t_fstats *b, int rev);
int		sort_mtime(t_fstats *a, t_fstats *b, int rev);
void	sort_ls(t_fstats **lst, int (*f)(t_fstats*, t_fstats*, int), int rev);

/*
** ACTUAL PRINTING STUFF
*/

void	get_ls_columns_rows(t_size *ref, t_queue *grp);
size_t	get_spaces_to_add(size_t pre, t_queue *grp);
void	print_elems(t_queue *queue);

#endif

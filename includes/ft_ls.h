/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/21 17:34:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** MAIN HEADER FILE
*/

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

int		get_file_content(t_group *alst, char *d_name);
int		get_dir_content(t_group *alst, int chk_lnk);
void	free_dir_elem_content(t_elem **alst);
void	free_dir_content(t_elem **alst);

/*
** DB Filling
*/

int		fill_elem(char *d_name, t_elem *elem, t_group *grp);
char	get_ifmt_char(mode_t mode, int bigf);
char	get_perm_char(mode_t mode, mode_t mask);
char	get_acl_xattrs_char(t_elem *elem);

/*
** DB SORTING
*/

int		ft_group_sortalpha(t_group *a, t_group *b, int rev);
int		ft_group_sortmtime(t_group *a, t_group *b, int rev);
void	ft_group_mergesort(t_group **lst, int (*f)(t_group*, t_group*, int), \
	int rev);
void	launch_groups_sort(t_group **grps);

int		sort_alpha(t_elem *a, t_elem *b, int rev);
int		sort_mtime(t_elem *a, t_elem *b, int rev);
void	sort_ls(t_elem **lst, int (*f)(t_elem*, t_elem*, int), int rev);

/*
** ACTUAL PRINTING STUFF
*/

void	print_human_fmt(off_t size);
void	print_elem_size(t_elem *elm, t_group *grp);
void	get_ls_columns_rows(t_size *ref, t_group *grp);
size_t	get_spaces_to_add(size_t pre, t_group *grp);
void	print_elems(t_group *grp);

/*
** MISC
*/

void	fillinf(size_t *dest, size_t new);
void	ls_elem_err(char *path, int err);

#endif

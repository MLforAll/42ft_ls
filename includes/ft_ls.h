/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 20:15:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ls_data.h"
# include "ls_args.h"
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
** QUEUING
*/

int		list_dirs(t_list **paths, int add_nl);

/*
** DB MGMT
*/

t_blkc	get_file_content(t_queue *alst, t_fstats ***dc, char *d_name);
t_blkc	get_dir_content(t_queue *alst);
void	free_dir_content(t_fstats **alst);

/*
** DB Filling/Freeing
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

void	print_elems(t_queue *queue, t_list **reclst);

/*
** t_list UTILITIES
*/

void	ft_lstdelf(void *data, size_t data_size);
int		ft_lst_sortalpha(t_list *a, t_list *b);
void	ft_lstpushback(t_list **alst, void *data, size_t data_content);
t_list	*ft_lstpushback_edit(t_list **alst, t_list *new);

/*
** t_queue UTILITIES
*/

t_queue	*ft_queue_new(char *dname);
void	ft_queue_pb(t_queue **aq, t_queue *new);
void	ft_queue_pf(t_queue **aq, t_queue *new);
void	ft_queue_free(t_queue **aq);
void	ft_queue_del(t_queue **aqueue);

#endif

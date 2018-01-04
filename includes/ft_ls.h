/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 04:36:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ls_data.h"
# include "ls_args.h"
# include "libft.h"

# define PRGM_NAME	"ft_ls"
# define OPTEXISTS(b, opt)	(b & opt) != 0

/*
** QUEUING
*/

int		list_dirs(t_list *paths, int optsb, int add_nl);

/*
** ARGUMENTS
*/

int		option_valid(char c);
int		detect_options(int ac, char **av, int *idx);

/*
** DB MGMT
*/

int		get_dir_content(t_queue *alst, int show_all);
void	free_dir_content(t_fstats **alst);
size_t	dclen(t_fstats *dc);

/*
** DB Filling/Freeing
**/

int		fill_fstats(t_dirent *dird, t_fstats *fstats, t_queue *queue);

/*
** DB SORTING
*/

int		sort_alpha(t_fstats *a, t_fstats *b, int rev);
int		sort_mtime(t_fstats *a, t_fstats *b, int rev);
void	sort_ls(t_fstats **lst, int (*f)(t_fstats*, t_fstats*, int), int rev);

/*
** ACTUAL PRINTING STUFF
*/

void	print_dcs(t_queue *dcs, int optsb, int add_nl);

/*
** PRINTING UTILITIES
*/

void	ft_miniprintf(char *format, ...);
void	ft_putnbr_longlong(long long n);
void	print_int_width(int n, size_t width);
void	print_offt_width(off_t size, size_t width);
void	print_str_width(char *s, size_t width);

/*
** t_list UTILITIES
*/

void	ft_lstdelf(void *data, size_t data_size);
void	ft_lstpushback(t_list **alst, void *data, size_t data_content);
t_list	*ft_lstpushback_edit(t_list **alst, t_list *new);

/*
** t_queue UTILITIES
*/

t_queue	*ft_queue_new(char *dname);
void	ft_queue_pb(t_queue **aq, t_queue *new);
void	ft_queue_del(t_queue **aqueue);

#endif

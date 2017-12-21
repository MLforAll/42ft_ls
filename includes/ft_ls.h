/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/21 19:55:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ls_data.h"
# include "ls_args.h"
# include "libft.h"

/*
** ACTUAL PRINTING STUFF
*/

void	list_dirs(t_list **targets, int optsb, int add_nl);

/*
** DB MGMT
*/

int		get_dir_content(const char *path, t_fstats **alst);
void	free_dir_content(t_fstats **alst);

/*
** DB SORTING
*/

int		sort_alpha(t_fstats *a, t_fstats *b, int rev);
int		sort_mtime(t_fstats *a, t_fstats *b, int rev);
void	sort_ls_lst(t_fstats **alst, int (*f)(t_fstats*, t_fstats*, int), int rev);

/*
** ARGUMENTS
*/

int		is_option_valid(char c);
int		detect_options(int ac, char **av);

/*
** t_list UTILITIES
*/

void	ft_lstdelf(void *data, size_t data_size);
void	ft_lstpushback(t_list **alst, t_list *new);
t_list	*ft_lstpushback_edit(t_list **alst, t_list *new);

#endif

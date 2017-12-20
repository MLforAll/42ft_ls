/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/20 19:14:40 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ls_data.h"
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

int		sort_revalpha(t_fstats *a, t_fstats *b);
int		sort_mtime(t_fstats *a, t_fstats *b);
void	sort_ls_lst(t_fstats **alst, int (*cmp)(t_fstats*, t_fstats*));

/*
** ARGUMENTS
*/

int		is_option_valid(char c);
int		detect_options(int ac, char **av);

/*
** UTILITIES
*/

void	ft_lstdelf(void *data, size_t data_size);
void	ft_lstpushback(t_list **alst, t_list *new);

#endif

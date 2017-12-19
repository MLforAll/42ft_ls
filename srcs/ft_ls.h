/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/19 22:05:32 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include "libft.h"

/*
** DATA STRUCT
*/

typedef struct 			s_fstats
{
	char			*fname;
	char			*fpath;
	char			ftype;
	char			*timec;
	off_t			size;
	nlink_t			nblink;
	char			*grname;
	char			*usrname;
	struct s_fstats	*next;
}						t_fstats;

/*
** SYS TYPEDEFS
*/

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_pw;
typedef struct group	t_group;

/*
** ACTUAL PRINTING STUFF
*/

void					list_dirs(t_list **targets, int optsb, int add_nl);

/*
** DB MGMT
*/

int						get_dir_content(const char *path, t_fstats **alst);
void					free_dir_content(t_fstats **alst);

/*
** UTILITIES
*/

void					ft_lstdelf(void *data, size_t data_size);
void					ft_lstpushback(t_list **alst, t_list *new);

#endif

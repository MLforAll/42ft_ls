/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:36:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/18 02:10:55 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_DATA_H
# define LS_DATA_H

# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>

/*
** MACROS
*/

# define HALFYRSEC			15552000

/*
** SYS TYPEDEFS
*/

# ifdef _DARWIN_FEATURE_64_BIT_INODE
#  define BLKCTYPE			blkcnt_t
# else
#  define BLKCTYPE			quad_t
# endif

typedef BLKCTYPE			t_blkc;

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_pw;
typedef struct group		t_grp;
typedef struct winsize		t_winsize;

/*
** DATA STRUCT
*/

typedef struct				s_elem
{
	char				*fname;
	char				*fpath;
	char				*sympath;
	char				*usrname;
	char				*grname;
	char				*xattrs;
	ssize_t				lxattr;
	t_stat				st;
	struct s_elem		*next;
}							t_elem;

/*
** GROUP (a.k.a FOLDER)
*/

typedef struct				s_group
{
	char				*grp_name;
	t_elem				*elems;
	t_blkc				total;
	size_t				nbfiles;
	size_t				maxlens[6];
	struct s_group		*next;
}							t_group;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:36:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/12 18:21:20 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_DATA_H
# define LS_DATA_H

# include <sys/types.h>
# include <sys/stat.h>

/*
** MACROS
*/

# define HALFYRSEC			15552000

/*
** SYS TYPEDEFS
*/

# ifdef _DARWIN_FEATURE_64_BIT_INODE
typedef blkcnt_t			t_blkc;
# else
typedef quad_t				t_blkc;
# endif

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_pw;
typedef struct group		t_group;
typedef struct winsize		t_winsize;

/*
** DATA STRUCT
*/

typedef struct				s_fstats
{
	char				*fname;
	char				*fpath;
	char				*sympath;
	char				*usrname;
	char				*grname;
	t_stat				st;
	struct s_fstats		*next;
}							t_fstats;

/*
** GROUP (a.k.a FOLDER)
*/

typedef struct				s_queue
{
	char				*dname;
	t_fstats			*dc;
	t_blkc				total;
	size_t				nbfiles;
	size_t				maxlens[6];
	struct s_queue		*next;
}							t_queue;

#endif

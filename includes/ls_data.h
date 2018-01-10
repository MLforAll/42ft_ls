/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:36:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 18:55:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_DATA_H
# define LS_DATA_H

# include <sys/types.h>
# include <sys/stat.h>

/*
** DEFINES
*/

# define HALFYRSEC			15552000

/*
** SYS TYPEDEFS
*/

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_pw;
typedef struct group		t_group;

#ifdef _DARWIN_FEATURE_64_BIT_INODE
typedef blkcnt_t			t_blkc;
#else
typedef quad_t				t_blkc;
#endif

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
** QUEUE (ERR MGMT)
*/

typedef struct				s_queue
{
	char				*dname;
	t_fstats			*dc;
	quad_t				total;
	size_t				maxlens[5];
	struct s_queue		*next;
}							t_queue;

#endif

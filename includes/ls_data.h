/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:36:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 23:01:08 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_DATA_H
# define LS_DATA_H

# include <sys/types.h>

/*
** SYS TYPEDEFS
*/

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_pw;
typedef struct group		t_group;

/*
** DATA STRUCT
*/

typedef struct				s_fstats
{
	char				*fname;
	char				*fpath;
	mode_t				fmode;
	time_t				mtime;
	off_t				size;
	quad_t				nbblk;
	nlink_t				nblink;
	char				*grname;
	char				*usrname;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:36:54 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/15 18:09:47 by kdumarai         ###   ########.fr       */
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
** SIZE STRUCT (W/H -- COLS/ROWS)
*/

typedef struct			s_size
{
	size_t		width;
	size_t		height;
}						t_size;

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

/*
** t_fstats UTILITIES
*/

void						ft_dcadd(t_fstats **alst, t_fstats *new);
t_fstats					*ft_dcnew(void);
t_fstats					*ft_dcnnext_elem(t_fstats *alst, size_t len);

/*
** t_queue UTILITIES
*/

t_queue						*ft_queue_new(char *dname);
void						ft_queue_pb(t_queue **aq, t_queue *new);
void						ft_queue_pf(t_queue **aq, t_queue *new);
void						ft_queue_free(t_queue **aq);
void						ft_queue_del(t_queue **aqueue);

#endif

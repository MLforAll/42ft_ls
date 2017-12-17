/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 01:58:49 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/17 05:30:07 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include "libft.h"

typedef struct 			s_fstats
{
	char	*fname;
	char	*timec;
	off_t	size;
	nlink_t	nblink;
	char	*grname;
	char	*usrname;
}						t_fstats;

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

void					get_dir_content(const char *path);

#endif

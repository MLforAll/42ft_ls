/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_columns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:56:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/15 18:20:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "ft_ls.h"

/*
** This function retreive the properties required for columns display
*/

int		get_ls_columns_rows(t_size *ref, t_queue *grp)
{
	t_winsize		ws;
	size_t			maxlen;

	if (ioctl(1, TIOCGWINSZ, &ws) == -1)
	{
		ft_bzero(ref, sizeof(t_size));
		return (0);
	}
	maxlen = grp->maxlens[5] + (OPTEXISTS(A_FFOPT) ? 2 : 1);
	if (OPTEXISTS(A_SOPT))
		maxlen += grp->maxlens[0];
	ref->width = ws.ws_col / maxlen;
	if (ref->width == 0)
		ref->width = 1;
	ref->height = grp->nbfiles / ref->width + (grp->nbfiles % ref->width != 0);
	return (1);
}

size_t	get_spaces_to_add(size_t pre, t_queue *grp)
{
	size_t	ret;

	ret = (grp->maxlens[5] > pre) ? grp->maxlens[5] - pre : 0;
	ret += (pre > grp->maxlens[5] || !(OPTEXISTS(A_FFOPT))) ? 1 : 2;
	return (ret);
}

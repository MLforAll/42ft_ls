/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lsqueue_fts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:45:45 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/23 21:41:35 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls_data.h"

t_lsqueue	*ft_lsqueue_new(char *dname, t_fstats *dc, int total)
{
	t_lsqueue	*new;

	if (!(new = (t_lsqueue*)malloc(sizeof(t_lsqueue))))
		return (NULL);
	new->dname = ft_strdup(dname);
	new->dc = dc;
	new->total = total;
	new->next = NULL;
	return (new);
}

void		ft_lsqueue_pb(t_lsqueue **aqueue, char *dname, t_fstats *dc, int total)
{
	t_lsqueue	*bw;

	if (!aqueue)
		return ;
	if (!*aqueue)
	{
		*aqueue = ft_lsqueue_new(dname, dc, total);
		return ;
	}
	bw = *aqueue;
	while (bw->next)
		bw = bw->next;
	bw->next = ft_lsqueue_new(dname, dc, total);
}

void	ft_lsqueue_del(t_lsqueue **aqueue)
{
	t_lsqueue	**tmp;
	t_lsqueue	*bak;

	tmp = aqueue;
	while (*tmp)
	{
		bak = (*tmp)->next;
		ft_strdel(&(*tmp)->dname);
		free(*tmp);
		*tmp = NULL;
		tmp = &bak;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_queue_mgmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:45:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/06 17:00:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls_data.h"

t_queue		*ft_queue_new(char *dname)
{
	t_queue		*new;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	new->dname = ft_strdup(dname);
	ft_bzero((void*)new->maxlens, sizeof(size_t) * 5);
	new->total = 0;
	new->dc = NULL;
	new->next = NULL;
	return (new);
}

void		ft_queue_pb(t_queue **aq, t_queue *new)
{
	t_queue		*bw;

	if (!aq)
		return ;
	if (!*aq)
	{
		*aq = new;
		return ;
	}
	bw = *aq;
	while (bw->next)
		bw = bw->next;
	bw->next = new;
}

void		ft_queue_pf(t_queue **aq, t_queue *new)
{
	t_queue		*tmp;

	if (!aq)
		return ;
	if (!*aq)
	{
		*aq = new;
		return ;
	}
	tmp = *aq;
	*aq = new;
	(*aq)->next = tmp;
}

void		ft_queue_del(t_queue **aq)
{
	t_queue		**tmp;
	t_queue		*bak;

	tmp = aq;
	while (*tmp)
	{
		bak = (*tmp)->next;
		ft_strdel(&(*tmp)->dname);
		free(*tmp);
		*tmp = NULL;
		tmp = &bak;
	}
}

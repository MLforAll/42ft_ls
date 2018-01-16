/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_queue_mgmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:45:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 20:30:44 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

t_queue		*ft_queue_new(char *dname)
{
	t_queue		*new;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	new->dname = (dname) ? ft_strdup(dname) : NULL;
	new->dc = NULL;
	new->total = 0;
	new->nbfiles = 0;
	ft_bzero((void*)new->maxlens, sizeof(new->maxlens));
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
	if (!aq)
		return ;
	if (!*aq)
	{
		*aq = new;
		return ;
	}
	new->next = *aq;
	*aq = new;
}

void		ft_queue_free(t_queue **aq)
{
	if ((*aq)->dname)
		ft_strdel(&(*aq)->dname);
	if ((*aq)->dc)
		free_dir_content(&(*aq)->dc);
	free(*aq);
	*aq = NULL;
}

void		ft_queue_del(t_queue **aq)
{
	t_queue		*tmp;
	t_queue		*bak;

	tmp = *aq;
	while (tmp)
	{
		bak = tmp->next;
		if (tmp)
			ft_queue_free(&tmp);
		tmp = bak;
	}
}

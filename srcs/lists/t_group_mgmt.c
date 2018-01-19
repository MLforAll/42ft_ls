/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_group_mgmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:45:45 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/18 23:11:38 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

t_group		*ft_group_new(char *grp_name)
{
	t_group		*new;

	if (!(new = (t_group*)malloc(sizeof(t_group))))
		return (NULL);
	new->grp_name = (grp_name) ? ft_strdup(grp_name) : NULL;
	new->elems = NULL;
	new->err = -1;
	new->total = 0;
	new->nbfiles = 0;
	ft_bzero((void*)new->maxlens, sizeof(new->maxlens));
	new->next = NULL;
	return (new);
}

void		ft_group_push(t_group **agrp, t_group *new)
{
	t_group		*bw;

	if (!agrp || !new)
		return ;
	if (!*agrp)
	{
		*agrp = new;
		return ;
	}
	bw = *agrp;
	while (bw->next)
		bw = bw->next;
	bw->next = new;
}

void		ft_group_add(t_group **agrp, t_group *new)
{
	if (!agrp || !new)
		return ;
	if (!*agrp)
	{
		*agrp = new;
		return ;
	}
	new->next = *agrp;
	*agrp = new;
}

void		ft_group_del(t_group **agrp)
{
	if (!agrp || !*agrp)
		return ;
	if ((*agrp)->grp_name)
		ft_strdel(&(*agrp)->grp_name);
	if ((*agrp)->elems)
		free_dir_content(&(*agrp)->elems);
	free(*agrp);
	*agrp = NULL;
}

void		ft_group_delall(t_group **agrp)
{
	t_group		*tmp;
	t_group		*bak;

	tmp = *agrp;
	while (tmp)
	{
		bak = tmp->next;
		if (tmp)
			ft_group_del(&tmp);
		tmp = bak;
	}
}

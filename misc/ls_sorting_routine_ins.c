/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sorting_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:30:02 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/19 01:49:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	insert_elsewhere(t_elem *bw, t_elem *curr, \
	int (*cmp)(t_elem *a, t_elem *b, int), int rev)
{
	while (bw)
	{
		if (!bw->next || !cmp(curr, bw->next, rev))
		{
			curr->next = bw->next;
			bw->next = curr;
			return ;
		}
		bw = bw->next;
	}
}

void			sort_ls(t_elem **lst, int (*f)(t_elem*, t_elem*, int), int rev)
{
	t_elem	*ret;
	t_elem	*curr;

	if (!*lst || !(*lst)->next)
		return ;
	ret = NULL;
	while (*lst)
	{
		curr = *lst;
		*lst = (*lst)->next;
		if (!ret || !f(curr, ret, rev))
		{
			curr->next = ret;
			ret = curr;
		}
		else
			insert_elsewhere(ret, curr, f, rev);
	}
	*lst = ret;
}

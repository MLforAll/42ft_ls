/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:23:13 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/19 22:10:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_ls_lst(t_fstats **fstats, int (*cmp)(t_fstats*, t_fstats*))
{
	t_fstats	*curr;
	t_fstats	*prev;
	t_fstats	*tmp;

	curr = *fstats;
	prev = *fstats;
	while (curr->next)
	{
		if (!cmp(curr, curr->next))
		{
			prev->next = curr->next;
			tmp = curr;
			curr->next = curr;
			tmp->next = tmp->next->next;
			curr = *fstats;
			prev = *fstats;
		}
		else
			curr = curr->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:23:13 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/29 18:03:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** SORT FUNCTIONS RETURN:
**	1 if swapping is needed
**	0 otherwise
*/

int		sort_alpha(t_fstats *a, t_fstats *b, int rev)
{
	int		diff;

	diff = ft_strcmp(a->fname, b->fname);
	if (diff == 0)
		return (0);
	return ((diff > 0) == !rev);
}

int		sort_mtime(t_fstats *a, t_fstats *b, int rev)
{
	if (a->mtime == b->mtime)
		return (sort_alpha(a, b, rev));
	return ((a->mtime < b->mtime) == !rev);
}

void	sort_ls(t_fstats **lst, int (*f)(t_fstats*, t_fstats*, int), int rev)
{
	t_fstats	*curr;
	t_fstats	*prev;
	t_fstats	*tmp;

	curr = *lst;
	while (curr->next)
	{
		prev = (curr == *lst) ? NULL : prev;
		if (f(curr, curr->next, rev))
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			tmp = curr->next->next;
			curr->next->next = curr;
			curr->next = tmp;
			curr = *lst;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

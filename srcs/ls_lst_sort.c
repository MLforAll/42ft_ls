/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:23:13 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/20 21:45:22 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_alpha(t_fstats *a, t_fstats *b)
{
	return (ft_strcmp(a->fname, b->fname) > 0);
}

int		sort_revalpha(t_fstats *a, t_fstats *b)
{
	return (ft_strcmp(a->fname, b->fname) < 0);
}

int		sort_mtime(t_fstats *a, t_fstats *b)
{
	return (a->mtime < b->mtime);
}

void		sort_ls_lst(t_fstats **alst, int (*cmp)(t_fstats*, t_fstats*))
{
	t_fstats	*curr;
	t_fstats	*prev;
	t_fstats	*tmp;

	curr = *alst;
	while (curr->next)
	{
		prev = (curr == *alst) ? NULL : prev;
		if (cmp(curr, curr->next))
		{
			if (prev)
				prev->next = curr->next;
			else
				*alst = curr->next;
			tmp = curr->next->next;
			curr->next->next = curr;
			curr->next = tmp;
			curr = *alst;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

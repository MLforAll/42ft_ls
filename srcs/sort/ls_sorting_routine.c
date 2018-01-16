/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sorting_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:30:02 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 14:06:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_fstats	*get_middle(t_fstats *lst)
{
	t_fstats	*fast;
	t_fstats	*ret;
	int			i;

	if (!lst)
		return (NULL);
	fast = lst->next;
	ret = lst;
	i = 0;
	while (fast)
	{
		fast = fast->next;
		if (i)
			ret = ret->next;
		i = !i;
	}
	return (ret);
}

static void		split_lst(t_fstats *lst, t_fstats **side_a, t_fstats **side_b)
{
	t_fstats	*middle;

	if (!lst || !lst->next)
	{
		*side_a = lst;
		*side_b = NULL;
		return ;
	}
	middle = get_middle(lst);
	*side_a = lst;
	*side_b = middle->next;
	middle->next = NULL;
}

static t_fstats	*merge_lists(t_fstats *a, t_fstats *b, \
	int (*cmp)(t_fstats*, t_fstats*, int), int rev)
{
	t_fstats	*ret;

	if (!a && !b)
		return (NULL);
	else if (!a)
		return (b);
	else if (!b)
		return (a);
	if (!cmp(a, b, rev))
	{
		ret = a;
		ret->next = merge_lists(a->next, b, cmp, rev);
	}
	else
	{
		ret = b;
		ret->next = merge_lists(a, b->next, cmp, rev);
	}
	return (ret);
}

void			sort_ls(t_fstats **lst, int (*f)(t_fstats*, t_fstats*, int), \
	int rev)
{
	t_fstats	*side_a;
	t_fstats	*side_b;

	if (!*lst || !(*lst)->next)
		return ;
	split_lst(*lst, &side_a, &side_b);
	sort_ls(&side_a, f, rev);
	sort_ls(&side_b, f, rev);
	*lst = merge_lists(side_a, side_b, f, rev);
}

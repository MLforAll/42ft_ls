/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_group_sorting_routine.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:30:02 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/20 20:02:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** The same as the other 'routine' file except it's for t_group
**														a.k.a struct s_group
*/

static t_group	*get_middle(t_group *lst)
{
	t_group		*fast;
	t_group		*ret;
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

static void		split_lst(t_group *lst, t_group **side_a, t_group **side_b)
{
	t_group		*middle;

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

static t_group	*merge_lists(t_group *a, t_group *b, \
	int (*cmp)(t_group*, t_group*, int), int rev)
{
	t_group		*ret;

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

void			ft_group_mergesort(t_group **lst, \
	int (*f)(t_group*, t_group*, int), int rev)
{
	t_group		*side_a;
	t_group		*side_b;

	if (!*lst || !(*lst)->next)
		return ;
	split_lst(*lst, &side_a, &side_b);
	ft_group_mergesort(&side_a, f, rev);
	ft_group_mergesort(&side_b, f, rev);
	*lst = merge_lists(side_a, side_b, f, rev);
}

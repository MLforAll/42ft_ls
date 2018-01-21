/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sorting_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:30:02 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/18 23:00:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** merge sort for lists
** it splits each 'side' of the list recursively
** 'till it only gets pairs of 1.
** at this point, it just changes the pointers to sort the list
*/

static t_elem	*get_middle(t_elem *lst)
{
	t_elem		*fast;
	t_elem		*ret;
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

static void		split_lst(t_elem *lst, t_elem **side_a, t_elem **side_b)
{
	t_elem		*middle;

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

static t_elem	*merge_lists(t_elem *a, t_elem *b, \
	int (*cmp)(t_elem*, t_elem*, int), int rev)
{
	t_elem		*ret;

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

void			sort_ls(t_elem **lst, int (*f)(t_elem*, t_elem*, int), int rev)
{
	t_elem		*side_a;
	t_elem		*side_b;

	if (!*lst || !(*lst)->next)
		return ;
	split_lst(*lst, &side_a, &side_b);
	sort_ls(&side_a, f, rev);
	sort_ls(&side_b, f, rev);
	*lst = merge_lists(side_a, side_b, f, rev);
}

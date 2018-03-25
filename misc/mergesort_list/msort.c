/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:30:02 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 12:48:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tlist.h"

static t_list	*get_middle(t_list *lst)
{
	t_list	*fast;
	t_list	*ret;
	int		i;

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

static void split_lst(t_list *lst, t_list **side_a, t_list **side_b)
{
	t_list	*middle;

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

static t_list	*merge_lists(t_list *a, t_list *b)
{
	t_list	*ret;

	if (!a && !b)
		return (NULL);
	else if (!a)
		return (b);
	else if (!b)
		return (a);

	if (a->data <= b->data)
	{
		ret = a;
		ret->next = merge_lists(a->next, b);
	}
	else
	{
		ret = b;
		ret->next = merge_lists(a, b->next);
	}
	return (ret);
}

void	sort_lst_ms(t_list **lst)
{
	t_list	*side_a;
	t_list	*side_b;

	if (!*lst || !(*lst)->next)
		return ;
	split_lst(*lst, &side_a, &side_b);
	sort_lst_ms(&side_a);
	sort_lst_ms(&side_b);
	*lst = merge_lists(side_a, side_b);
}

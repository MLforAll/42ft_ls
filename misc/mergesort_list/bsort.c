/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:30:02 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 12:46:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tlist.h"

void	sort_lst_bs(t_list **lst)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*tmp;

	curr = *lst;
	while (curr->next)
	{
		prev = (curr == *lst) ? NULL : prev;
		if (curr->data > curr->next->data)
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

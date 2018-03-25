/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 21:01:51 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 12:37:22 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tlist.h"

void	add_node(t_list **lst, int n)
{
	t_list	*tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = (t_list*)malloc(sizeof(t_list));
		(*lst)->data = n;
		(*lst)->next = NULL;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_list*)malloc(sizeof(t_list));
	tmp->next->data = n;
	tmp->next->next = NULL;
}

void	free_lst(t_list **lst)
{
	t_list	*bak;

	while (*lst)
	{
		bak = (*lst)->next;
		free(*lst);
		*lst = bak;
	}
	*lst = NULL;
}

void	show_lst(t_list *lst, char *name)
{
	int		idx;

	idx = 0;
	puts(name);
	while (lst)
	{
		printf("lst #%i: %i\n", idx++, lst->data);
		lst = lst->next;
	}
}

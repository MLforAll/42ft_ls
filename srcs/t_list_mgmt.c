/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 14:32:09 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/19 18:15:18 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelf(void *data, size_t data_size)
{
	(void)data_size;
	ft_strdel((char**)&data);
}

void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*bw;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	bw = *alst;
	while (bw->next)
		bw = bw->next;
	bw->next = new;
}

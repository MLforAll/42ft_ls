/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 14:32:09 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/23 18:23:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelf(void *data, size_t data_size)
{
	(void)data_size;
	ft_strdel((char**)&data);
}

void	ft_lstpushback(t_list **alst, void *data, size_t data_size)
{
	t_list	*bw;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = ft_lstnew(data, data_size);
		return ;
	}
	bw = *alst;
	while (bw->next)
		bw = bw->next;
	bw->next = ft_lstnew(data, data_size);
}

t_list	*ft_lstpushback_edit(t_list **alst, t_list *new)
{
	t_list	*bak;
	t_list	**toedit;

	if (!alst)
		return (NULL);
	if (*alst)
	{
		bak = *alst;
		toedit = alst;
	}
	else
	{
		bak = NULL;
		toedit = &(*alst)->next;
	}
	*toedit = new;
	*toedit = (*toedit)->next;
	return (bak);
}

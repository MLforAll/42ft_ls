/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 14:32:09 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/20 19:38:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "ft_lsprint.h"
#include "ls_data.h"
#include "libft.h"

/*
** t_list support functions
** those are complement for sorting, del etc
*/

/*
** Sort
*/

int		ft_lst_sortalpha(t_list *a, t_list *b, int rev)
{
	int		diff;

	diff = ft_strcmp((char*)a->content, (char*)b->content);
	if (diff == 0)
		return (0);
	return ((diff > 0) == !rev);
}

int		ft_lst_sortmtime(t_list *a, t_list *b, int rev)
{
	t_stat	sta;
	t_stat	stb;

	lstat((char*)a->content, &sta);
	lstat((char*)b->content, &stb);
	if (sta.st_mtime == stb.st_mtime)
	{
		if (sta.st_mtimespec.tv_nsec == stb.st_mtimespec.tv_nsec)
			return (ft_lst_sortalpha(a, b, rev));
		return ((sta.st_mtimespec.tv_nsec < stb.st_mtimespec.tv_nsec) == !rev);
	}
	return ((sta.st_mtime < stb.st_mtime) == !rev);
}

/*
** Add/Del
*/

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

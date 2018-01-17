/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_elem_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 17:22:31 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/17 21:15:30 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls_data.h"

t_elem		*ft_elem_new(void)
{
	t_elem	*ret;

	ret = (t_elem*)malloc(sizeof(t_elem));
	ft_bzero(ret, sizeof(t_elem));
	return (ret);
}

void		ft_elem_add(t_elem **alst, t_elem *new)
{
	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	new->next = *alst;
	*alst = new;
}

t_elem		*ft_elem_nnext(t_elem *alst, size_t len)
{
	if (!alst)
		return (NULL);
	while (alst && len--)
		alst = alst->next;
	return (alst);
}
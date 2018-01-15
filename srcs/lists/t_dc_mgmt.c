/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dc_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 17:22:31 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/15 18:18:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls_data.h"

t_fstats	*ft_dcnew(void)
{
	t_fstats	*ret;

	ret = (t_fstats*)malloc(sizeof(t_fstats));
	ft_bzero(ret, sizeof(t_fstats));
	return (ret);
}

void		ft_dcadd(t_fstats **alst, t_fstats *new)
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

t_fstats	*ft_dcnnext_elem(t_fstats *alst, size_t len)
{
	if (!alst)
		return (NULL);
	while (alst && len--)
		alst = alst->next;
	return (alst);
}

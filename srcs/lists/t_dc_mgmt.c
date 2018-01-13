/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dc_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 17:22:31 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/13 17:54:28 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_data.h"
#include <stdlib.h>

t_fstats	*ft_dcnew(void)
{
	return ((t_fstats*)malloc(sizeof(t_fstats)));
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
	unsigned int	cnt;

	if (!alst)
		return (NULL);
	cnt = 0;
	while (alst && cnt++ < len)
		alst = alst->next;
	return (alst);
}

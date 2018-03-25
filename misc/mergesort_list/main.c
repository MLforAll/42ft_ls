/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:45:24 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 12:50:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tlist.h"

int		main(int ac, char **av)
{
	t_list	*lst;
	int		size;

	if (ac != 2)
	{
		puts("Please only provide 1 arg, size of lst");
		return (1);
	}
	size = atoi(av[1]);
	lst = NULL;
	while (size--)
		add_node(&lst, arc4random_uniform(100));
	show_lst(lst, "unsorted:");
#ifdef MS
	sort_lst_ms(&lst);
#else
	sort_lst_bs(&lst);
#endif
	show_lst(lst, "\nsorted:");
	free_lst(&lst);
	return (0);
}

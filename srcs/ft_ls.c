/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 02:04:52 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/26 12:06:19 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

#include <stdio.h>

static void	ls_usage(char illopt)
{
	printf("%s: illegal option -- %c\n", PRGM_NAME, illopt);
	printf("usage: %s [-Ralrt] [file ...]\n", PRGM_NAME);
	exit(1);
}

int			main(int ac, char **av)
{
	int			optsb;
	int			i;
	t_list		*targets;
	t_list		**tmp;

	i = 1;
	targets = NULL;
	optsb = detect_options(ac, av, &i);
	if (optsb < 0)
		ls_usage(-optsb);
	while (i < ac)
	{
		if (!targets)
			tmp = &targets;
		else
			tmp = &(*tmp)->next;
		*tmp = ft_lstnew(av[i], ft_strlen(av[i]) + 1);
		i++;
	}
	if (!targets)
		targets = ft_lstnew(".", 2);
	return (list_dirs(targets, optsb, 0));
}

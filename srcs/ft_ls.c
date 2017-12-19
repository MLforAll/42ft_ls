/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 02:04:52 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/19 20:22:33 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

#include <stdio.h>

int			is_option_valid(char c)
{
	if (c == 'l')
		return (1);
	if (c == 'a')
		return (2);
	if (c == 'r')
		return (4);
	if (c == 't')
		return (8);
	if (c == 'R')
		return (16);
	return (0);
}

int			detect_options(int ac, char **av)
{
	int					retb;
	unsigned int		i;
	size_t				alen;
	int					validret;

	retb = 0;
	i = 1;
	if (ac > 1)
	{
		if (av[1][0] == '-')
		{
			alen = ft_strlen(av[1]);
			while (i < alen)
			{
				if (!(validret = is_option_valid(av[1][i])))
					return (-av[1][i]);
				retb |= validret;
				i++;
			}
		}
	}
	return (retb);
}

static void	ls_usage(const char *prgm_name, char illopt)
{
	printf("%s: illegal option -- %c\n", prgm_name, illopt);
	printf("usage: %s [-Ralrt] [file ...]\n", prgm_name);
	exit(1);
}

int			main(int ac, char **av)
{
	int		optsb;
	int		i;
	t_list	*targets;
	t_list	**tmp;

	i = 0;
	targets = NULL;
	optsb = detect_options(ac, av);
	if (optsb < 0)
		ls_usage("ft_ls", -optsb);
	else if (optsb > 0)
		i++;
	while (++i < ac)
	{
		if (!targets)
			tmp = &targets;
		else
			tmp = &(*tmp)->next;
		*tmp = ft_lstnew(av[i], ft_strlen(av[i]) + 1);
	}
	list_dirs(&targets, optsb, 0);
	return (0);
}

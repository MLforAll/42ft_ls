/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:43:21 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/21 21:58:05 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_args.h"
#include "libft.h"

/*
** OPTIONS BINARY VALUES: SEE LS_ARGS.H
*/

int		is_option_valid(char c)
{
	if (c == 'l')
		return (A_LOPT);
	if (c == 'a')
		return (A_AOPT);
	if (c == 'r')
		return (A_ROPT);
	if (c == 't')
		return (A_TOPT);
	if (c == 'R')
		return (A_RROPT);
	return (0);
}

int		detect_options(int ac, char **av)
{
	int					retb;
	unsigned int		i;
	int					p;
	size_t				alen;
	int					validret;

	retb = 0;
	p = 1;
	if (ac == 1)
		return (0);
	while (p < ac)
	{
		if (*av[p] == '-')
		{
			i = 1;
			alen = ft_strlen(av[p]);
			while (i < alen)
			{
				if (!(validret = is_option_valid(av[p][i])))
					return (-av[p][i]);
				retb |= validret;
				i++;
			}
		}
		p++;
	}
	return (retb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:43:21 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/21 18:20:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** OPTIONS BINARY VALUES:
** 0000 0001: -l (0x1)
** 0000 0010: -a (0x2)
** 0000 0100: -r (0x4)
** 0000 1000: -t (0x8)
** 0001 0000: -R (0x10)
*/

int		is_option_valid(char c)
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

int		detect_options(int ac, char **av)
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

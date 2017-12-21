/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:43:21 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/21 19:57:59 by kdumarai         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:43:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/06 21:29:52 by kdumarai         ###   ########.fr       */
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
	if (c == 's')
		return (A_SOPT);
	if (c == 'F')
		return (A_FFOPT);
	return (0);
}

int		detect_options(int ac, char **av, int *idx)
{
	int					retb;
	unsigned int		i;
	size_t				alen;
	int					validret;

	retb = 0;
	while (*idx < ac)
	{
		if (*av[*idx] != '-')
			break ;
		i = 1;
		alen = ft_strlen(av[*idx]);
		if (alen == 1)
			break ;
		while (i < alen)
		{
			if (!(validret = is_option_valid(av[*idx][i])))
				return (-av[*idx][i]);
			retb |= validret;
			i++;
		}
		*idx += 1;
	}
	return (retb);
}

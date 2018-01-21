/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:43:21 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/21 17:34:00 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ls_args_equivalence.h"

/*
** OPTIONS BINARY VALUES: SEE LS_ARGS.H
**
** A_XOPT
** ARGUMENT_XOPTION
*/

static int	is_option_valid(char c)
{
	int		idx;

	idx = 0;
	while (g_lsargs_equi[idx].c && g_lsargs_equi[idx].bcode)
	{
		if (c == g_lsargs_equi[idx].c)
			return (g_lsargs_equi[idx].bcode);
		idx++;
	}
	return (0);
}

static int	change_override(int optsb, int last)
{
	if ((last == A_LOPT || last == A_NOPT) && optsb & A_1OPT)
		return (optsb ^ A_1OPT);
	if (last == A_1OPT && optsb & A_LOPT)
		return (optsb ^ A_LOPT);
	return (optsb);
}

int			detect_options(int ac, char **av, int *idx)
{
	int					retb;
	unsigned int		i;
	size_t				alen;
	int					validret;

	retb = 0;
	while (*idx < ac && *av[*idx] == '-')
	{
		if (!ft_strcmp(av[*idx], "--"))
		{
			(*idx)++;
			break ;
		}
		i = 0;
		if ((alen = ft_strlen(av[*idx])) == 1)
			break ;
		while (++i < alen)
		{
			if (!(validret = is_option_valid(av[*idx][i])))
				return (-av[*idx][i]);
			retb = change_override(retb |= validret, validret);
		}
		*idx += 1;
	}
	return (retb);
}

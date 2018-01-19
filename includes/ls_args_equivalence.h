/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args_equivalence.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:07:27 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/19 03:59:21 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_ARGS_EQUIVALENCE_H
# define LS_ARGS_EQUIVALENCE_H

# include "ls_args.h"

typedef struct	s_lsargs
{
	char	c;
	int		bcode;
}				t_lsargs;

t_lsargs	g_lsargs_equi[] =
{
	{'l', A_LOPT},
	{'a', A_AOPT},
	{'r', A_ROPT},
	{'t', A_TOPT},
	{'R', A_RROPT},
	{'s', A_SOPT},
	{'F', A_FFOPT},
	{'G', A_GGOPT},
	{'1', A_1OPT},
	{'@', A_ATOPT},
	{'h', A_HOPT},
	{'n', A_NOPT},
	{0, 0}
};

#endif

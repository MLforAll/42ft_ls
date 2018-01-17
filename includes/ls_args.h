/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_args.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:55:06 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/17 20:33:23 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_ARGS_H
# define LS_ARGS_H

/*
** OPTIONS BINARY VALUES:
** 0000 0000 0001: -l (0x1)
** 0000 0000 0010: -a (0x2)
** 0000 0000 0100: -r (0x4)
** 0000 0000 1000: -t (0x8)
** 0000 0001 0000: -R (0x10)
** 0000 0010 0000: -s (0x20)
** 0000 0100 0000: -F (0x40)
** 0000 1000 0000: -G (0x80)
** 0001 0000 0000: -1 (0x100)
** 0010 0000 0000: -@ (0x200)
*/

# define A_LOPT			0x1
# define A_AOPT			0x2
# define A_ROPT			0x4
# define A_TOPT			0x8
# define A_RROPT		0x10
# define A_SOPT			0x20
# define A_FFOPT		0x40
# define A_GGOPT		0x80
# define A_1OPT			0x100
# define A_ATOPT		0x200

# define ARGS_ERR_LST	"-FGR@alrst1"

/*
** GLOBAL: OPTIONS
*/

int		g_opts;

# define OPTEXISTS(opt)	(g_opts & opt) != 0

/*
** ARGUMENTS FUNTION
*/

int		detect_options(int ac, char **av, int *idx);

#endif

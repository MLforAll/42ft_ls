/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 02:33:00 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/19 18:21:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_float_digit(float n, int fdigit)
{
	long	factor;

	factor = 1;
	while (fdigit--)
		factor *= 10;
	return ((int)(n * factor) % 10);
}

void		print_human_fmt(off_t size)
{
	off_t	size_factor;
	float	size_dup;
	int		size_float;
	char	*size_char;

	size_factor = 1024;
	size_dup = (float)size;
	size_char = "BKGTP";
	while (size_dup >= 1024)
	{
		size_dup /= size_factor;
		size_char += (size_char + 1 != NULL);
		size_factor *= 1024;
	}
	size_float = get_float_digit(size_dup, 1) \
				+ (get_float_digit(size_dup, 2) > 4);
	size_dup += (size_float > 9);
	size_float = (size_float > 9) ? 0 : size_float;
	if (ft_nbrlen(size_dup) > 1 || *size_char == 'B')
		ft_lsprint("%4l%c", (off_t)size_dup + (size_float > 4), *size_char);
	else
		ft_lsprint("%2l.%i%c", (off_t)size_dup, size_float, *size_char);
}

void		print_elem_size(t_elem *elm, t_group *grp)
{
	if (S_ISCHR(elm->st.st_mode) || S_ISBLK(elm->st.st_mode))
		ft_lsprint("%3i, %3i", major(elm->st.st_rdev), minor(elm->st.st_rdev));
	else if (optexists(A_HOPT))
		print_human_fmt(elm->st.st_size);
	else
		ft_lsprint("%$l", grp->maxlens[4], elm->st.st_size);
}

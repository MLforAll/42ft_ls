/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:15:35 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/12 17:30:53 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** COLORS DATA
**
** array of 11 ints
** Each int rep a 10-bit value as follows:
**
** bxxxx bxxxx where:
**		b is a 'bold' bit
**		x is a 'value' bit
*/

static int	get_clr_id(mode_t mode)
{
	int		ret;

	ret = -1;
	if (S_ISDIR(mode))
		ret = 0;
	else if (S_ISLNK(mode))
		ret = 1;
	else if (S_ISSOCK(mode))
		ret = 2;
	else if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH)
		ret = 4;
	else if (S_ISBLK(mode))
		ret = 5;
	else if (S_ISCHR(mode))
		ret = 6;
	return (ret);
}

int			print_clr(mode_t mode)
{
	int		idx;
	int		color_codes[2];

	if (!g_clrs[11] || (idx = get_clr_id(mode)) == -1)
		return (0);
	if (idx == 4 && (mode & S_ISUID || mode & S_ISGID))
		idx = (mode & S_ISUID) ? 7 : 8;
	else if (idx == 0)
	{
		if (mode & S_IWOTH && mode & S_ISVTX)
			idx = 9;
		else if (mode & S_IWOTH && (mode & S_ISVTX) == 0)
			idx = 10;
	}
	if ((g_clrs[idx] & 0xF) == 0)
		color_codes[0] = 39;
	else
		color_codes[0] = 30 + (g_clrs[idx] & 0xF);
	if (((g_clrs[idx] >> 5) & 0xF) == 0)
		color_codes[1] = 49;
	else
		color_codes[1] = ((g_clrs[idx] >> 5) & 0xF) + 40;
	ft_lsprint("\033[%i;%i;%im", ((g_clrs[idx] & 0x10)) ? 1 : 0, \
			color_codes[0], color_codes[1]);
	return (1);
}

void		detect_colors(char *entry)
{
	int		idxs[2];
	int		shift;
	int		value;

	idxs[0] = 0;
	idxs[1] = 22;
	shift = 0;
	g_clrs[11] = 1;
	while (*entry && idxs[1]--)
	{
		if ((*entry < 'A' || (*entry > 'H' && *entry < 'a') || *entry > 'h')
			&& *entry != 'x' && *entry != 'X')
			ft_lsprint("error: invalid character '%c' in LSCOLORS env var\n", \
				*entry);
		else if (*entry != 'x' && *entry != 'X')
		{
			value = ft_isupper((int)*entry) ? (((int)*entry - 65) | 0x10) \
										: (int)*entry - 97;
			g_clrs[idxs[0]] = g_clrs[idxs[0]] | (value << shift);
		}
		idxs[0] += (shift == 5);
		shift = (shift == 0) ? 5 : 0;
		entry++;
	}
}

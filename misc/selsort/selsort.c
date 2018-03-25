/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:26:31 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/15 18:49:02 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	sort_tab(int *tab, size_t len)
{
	unsigned int	idx;
	unsigned int	pdx;
	int				smallest;
	int				sid;
	int				first;
	int				bak;

	idx = 0;
	while (idx < len)
	{
		pdx = idx;
		first = 1;
		while (pdx < len)
		{
			if (first || tab[pdx] < smallest)
			{
				first = 0;
				smallest = tab[pdx];
				sid = pdx;
			}
			pdx++;
		}
		bak = tab[idx];
		tab[idx] = tab[sid];
		tab[sid] = bak;
		idx++;
	}
}

void	show_tab(int *tab, size_t len)
{
	unsigned int	idx;

	idx = 0;
	while (idx < len)
	{
		printf("tab[%i] = %i\n", idx, tab[idx]);
		idx++;
	}
}

int		main(void)
{
	int				tab[320];
	size_t			len;
	unsigned int	cnt;

	cnt = 0;
	len = sizeof(tab) / sizeof(int);
	while (cnt < len)
		tab[cnt++] = arc4random_uniform(100);
	puts("unsorted:");
	show_tab(tab, len);
	puts("\nsorting...");
	sort_tab(tab, len);
	puts("\nsorted");
	show_tab(tab, len);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 16:29:58 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/23 21:41:29 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_ls.h"

/*
** THIS FILE IS A TEST FILE AND THUS
** REQUIRES TO ADD THE REQUIRED FILES WHEN COMPILING
**/

static void	ft_putllst(t_fstats *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		printf("elem no. %i: %s\n", i, lst->fname);
		i++;
		lst = lst->next;
	}
}

static void	lst_sort_test(void)
{
	t_fstats	*lst;

	printf("Creating list...\n");
	printf("total = %i\n", get_dir_content(".", &lst));
	printf("List created!\n");
	ft_putllst(lst);
	printf("\nSorting list...\n");
	sort_ls_lst(&lst, &sort_revalpha);
	printf("List sorted!\n");
	ft_putllst(lst);
	printf("\nFreeing lst...\n");
	free_dir_content(&lst);
	printf("List freed!\n");
}

int			main(void)
{
#ifdef SORT
	lst_sort_test();
#else
	printf("Please specify a test with -D + __TEST_NAME__");
#endif
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 02:04:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/09 19:11:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static void		ls_usage(char illopt)
{
	ft_lsprint("%s: illegal option -- %c\n", PRGM_NAME, illopt);
	ft_lsprint("usage: %s [-FGRalrst] [file ...]\n", PRGM_NAME);
	exit(1);
}

static char		*get_env_ptr(char **env, char *start)
{
	while (*env)
	{
		if (ft_strstart(*env, start))
			return (*env);
		env++;
	}
	return (NULL);
}

int				main(int ac, char **av, char **env)
{
	int			i;
	t_list		*targets;
	t_list		**tmp;

	i = 1;
	targets = NULL;
	g_optsb = (ac == 1) ? 0 : detect_options(ac, av, &i);
	if (g_optsb < 0)
		ls_usage(-g_optsb);
	ft_bzero(g_clrs, 11);
	if (OPTEXISTS(A_GGOPT) || get_env_ptr(env, "CLICOLOR="))
		detect_colors(get_env_ptr(env, "LSCOLORS="));
	while (i < ac)
	{
		if (!targets)
			tmp = &targets;
		else
			tmp = &(*tmp)->next;
		*tmp = ft_lstnew(av[i], ft_strlen(av[i]) + 1);
		i++;
	}
	if (!targets)
		targets = ft_lstnew(".", 2);
	return (list_dirs(targets, 0));
}

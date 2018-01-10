/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 02:04:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 19:22:38 by kdumarai         ###   ########.fr       */
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

static t_list	*get_paths(int idx, int ac, char **av)
{
	t_list		*ret;
	t_list		**tmp;

	ret = NULL;
	while (idx < ac)
	{
		if (!ret)
			tmp = &ret;
		else
			tmp = &(*tmp)->next;
		*tmp = ft_lstnew(av[idx], ft_strlen(av[idx]) + 1);
		idx++;
	}
	if (!ret)
		ret = ft_lstnew(".", 2);
	return (ret);
}

int				main(int ac, char **av, char **env)
{
	int			idx;
	t_list		*paths;
	int			err;

	idx = 1;
	g_optsb = (ac == 1) ? 0 : detect_options(ac, av, &idx);
	if (g_optsb < 0)
		ls_usage(-g_optsb);
	ft_bzero(g_clrs, 11);
	if (OPTEXISTS(A_GGOPT) || get_env_ptr(env, "CLICOLOR="))
		detect_colors(get_env_ptr(env, "LSCOLORS="));
	paths = get_paths(idx, ac, av);
	err = list_dirs(paths, 0);
	ft_lstdel(&paths, &ft_lstdelf);
	return (err);
}

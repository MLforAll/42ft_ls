/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 02:04:52 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/19 05:29:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

static void		ls_usage(char *dyn_prname, char illopt)
{
	ft_lsprint_fd(2, "%s: illegal option -- %c\n", dyn_prname, illopt);
	ft_lsprint_fd(2, "usage: %s [%s] [file ...]\n", PRGM_NAME, ARGS_ERR_LST);
	exit(1);
}

static char		*get_env_ptr(char **env, char *start)
{
	char	*ret;

	while (*env)
	{
		if ((ret = ft_strstart(*env, start)))
			return (ret + 1);
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
	char		*lscolors_entry;

	idx = 1;
	g_opts = (ac == 1) ? 0 : detect_options(ac, av, &idx);
	if (g_opts < 0)
		ls_usage(av[0], -g_opts);
	ft_bzero(g_clrs, 11);
	if (ft_isatty(1) && (optexists(A_GGOPT) || get_env_ptr(env, "CLICOLOR"))
		&& (lscolors_entry = get_env_ptr(env, "LSCOLORS")))
		detect_colors(lscolors_entry);
	paths = get_paths(idx, ac, av);
	return (list_dirs(&paths, 0));
}

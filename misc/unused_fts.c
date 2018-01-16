/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:44:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 14:50:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains functions
** that are not used in the final build.
** They are kept as they might be useful for other projects.
*/

/*
** t_fstats mgmt
*/

void		ft_dcpush(t_fstats **alst, t_fstats *new)
{
	t_fstats	*bw;
	t_fstats	**toedit;

	if (!alst)
		return ;
	if (!*alst)
		toedit = alst;
	else
	{
		bw = *alst;
		while (bw->next)
			bw = bw->next;
		toedit = &bw->next;
	}
	*toedit = new;
}

t_fstats	*ft_dcpush_edit(t_fstats **alst, t_fstats *new)
{
	t_fstats	*bw;
	t_fstats	**toedit;

	if (!alst)
		return (NULL);
	if (!*alst)
		toedit = alst;
	else
	{
		bw = *alst;
		while (bw->next)
			bw = bw->next;
		toedit = &bw->next;
	}
	*toedit = new;
	return (*toedit);
}

/*
** t_list mgmt
*/

t_list	*ft_lstpushback_edit(t_list **alst, t_list *new)
{
	t_list	*bw;
	t_list	**toedit;

	if (!alst)
		return (NULL);
	if (*alst)
		toedit = alst;
	else
	{
		bw = *alst;
		while (bw->next)
			bw = bw->next;
		toedit = &bw->next;
	}
	*toedit = new;
	return (*toedit);
}

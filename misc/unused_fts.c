/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:44:22 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/17 17:50:43 by kdumarai         ###   ########.fr       */
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

/*
** t_elem bubble sort
*/

void	sort_ls(t_elem **lst, int (*f)(t_elem*, t_elem*, int), int rev)
{
	t_elem	*curr;
	t_elem	*prev;
	t_elem	*tmp;
	curr = *lst;
	while (curr->next)
	{
		prev = (curr == *lst) ? NULL : prev;
		if (f(curr, curr->next, rev))
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			tmp = curr->next->next;
			curr->next->next = curr;
			curr->next = tmp;
			curr = *lst;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

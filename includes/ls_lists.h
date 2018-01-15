/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lists.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 19:08:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/15 18:16:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_LISTS_H
# define LS_LISTS_H

void		ft_dcadd(t_fstats **alst, t_fstats *new);
t_fstats	*ft_dcnew(void);
t_fstats	*ft_dcnnext_elem(t_fstats *alst, size_t len);

/*
** t_list UTILITIES
*/

void		ft_lstdelf(void *data, size_t data_size);
int			ft_lst_sortalpha(t_list *a, t_list *b);
void		ft_lstpushback(t_list **alst, void *data, size_t data_content);
t_list		*ft_lstpushback_edit(t_list **alst, t_list *new);

/*
** t_queue UTILITIES
*/

t_queue		*ft_queue_new(char *dname);
void		ft_queue_pb(t_queue **aq, t_queue *new);
void		ft_queue_pf(t_queue **aq, t_queue *new);
void		ft_queue_free(t_queue **aq);
void		ft_queue_del(t_queue **aqueue);

#endif

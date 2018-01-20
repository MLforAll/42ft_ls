/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lists.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 19:08:53 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/20 19:34:06 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_LISTS_H
# define LS_LISTS_H

/*
** t_group UTILITIES
*/

t_group		*ft_group_new(char *grp_name);
void		ft_group_push(t_group **agrp, t_group *new);
void		ft_group_add(t_group **agrp, t_group *new);
void		ft_group_del(t_group **agrp);
void		ft_group_delall(t_group **agrp);

/*
** t_elem UTILITIES
*/

t_elem		*ft_elem_new(void);
void		ft_elem_add(t_elem **alst, t_elem *new);
t_elem		*ft_elem_nnext(t_elem *alst, size_t len);

/*
** t_list UTILITIES
*/

void		ft_lstdelf(void *data, size_t data_size);
int			ft_lst_sortmtime(t_list *a, t_list *b, int rev);
int			ft_lst_sortalpha(t_list *a, t_list *b, int rev);
void		ft_lstpushback(t_list **alst, void *data, size_t data_content);

#endif

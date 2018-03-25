/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 21:01:51 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 12:46:50 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LIST_H
# define T_LIST_H

typedef struct		s_list
{
	int				data;
	struct s_list	*next;
}					t_list;

void	sort_lst_ms(t_list **lst);
void	sort_lst_bs(t_list **lst);

void	add_node(t_list **lst, int n);
void	free_lst(t_list **lst);
void	show_lst(t_list *lst, char *name);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsprint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:44:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 17:57:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LSPRINT_H
# define FT_LSPRINT_H

/*
** HEADER FOR FT_LSPRINT FUNCTION
** THIS IS A MINI-PRINTF
*/

/*
** Options Structure
** 'width' and 'max' correspond to min field width and precision
*/

typedef struct	s_opts
{
	size_t	width;
	size_t	max;
	int		justf;
}				t_opts;

/*
** PRINTING UTILITIES
*/

void			ft_lsprint(char *format, ...);
void			ft_lsprint_fd(int fd, char *format, ...);

/*
** Kind of private (or u have to setup the t_ops struct bf calling them)
*/

void			print_int_width_fd(int fd, int n, t_opts opts);
void			print_ll_width_fd(int fd, long long n, t_opts opts);
void			print_str_width_fd(int fd, char *s, t_opts opts);
void			print_char_width_fd(int fd, char c, t_opts opts);

#endif

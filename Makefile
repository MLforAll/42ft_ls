# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2017/12/23 21:36:51 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I includes -I ../Libft

LIBFT = ../Libft/libft.a
LIB = -L ../Libft -lft

SRCDIR = srcs
SRCS = srcs/ft_ls.c \
	srcs/ls_args.c \
	srcs/ls_get_properties.c \
	srcs/ls_lst_sort.c \
	srcs/ls_queuing.c \
	srcs/ls_print_lst.c \
	srcs/t_list_mgmt.c \
	srcs/t_lsqueue_fts.c

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(dir $(LIBFT))

$(NAME): $(OBJS)
	gcc -o $(NAME) $(LIB) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -z $@ ]; then mkdir -p $(dir $@); fi
	gcc $(CFLAGS) -c $< $(INCLUDES) -o $@

clean:
	make clean -C $(dir $(LIBFT))
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(dir $(LIBFT))
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/01/05 13:37:27 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I includes -I libft

LIBFT = libft/libft.a
LIB = -L libft -lft

SRCDIR = srcs
SRCS = $(SRCDIR)/ft_ls.c \
	$(SRCDIR)/ls_args.c \
	$(SRCDIR)/info/ls_get_properties.c \
	$(SRCDIR)/info/ls_fill_properties.c \
	$(SRCDIR)/info/ls_lst_sort.c \
	$(SRCDIR)/info/ls_queuing.c \
	$(SRCDIR)/display/ls_print_lst.c \
	$(SRCDIR)/display/ls_display_utils.c \
	$(SRCDIR)/display/ft_lsprint.c \
	$(SRCDIR)/lists/t_list_mgmt.c \
	$(SRCDIR)/lists/t_queue_mgmt.c

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(dir $(LIBFT))
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

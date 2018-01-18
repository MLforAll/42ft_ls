# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/01/18 18:38:30 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I includes -I libft

LIBFT = libft/libft.a
LIB = -L libft -lft

SRCDIR = srcs
SRCFILES = ft_ls.c \
	ls_args.c \
	ls_colors.c \
	info/ls_getchars.c \
	info/ls_get_properties.c \
	info/ls_fill_properties.c \
	info/ls_queuing.c \
	sort/ls_sorting_comps.c \
	sort/ls_sorting_routine.c \
	display/ls_print_lst.c \
	display/ls_columns.c \
	ft_lsprint/ft_lsprint.c \
	ft_lsprint/ft_lsprint_utils.c \
	lists/t_list_mgmt.c \
	lists/t_group_mgmt.c \
	lists/t_elem_mgmt.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PROJTEXT = \033[1;33mft_ls: \033[0;39m

all: lib $(NAME)

lib:
	@make -C $(dir $(LIBFT))

$(NAME): $(OBJS)
	@ printf "\r\033[K$(PROJTEXT)Compiling\n"
	@ printf "$(PROJTEXT)Linking\n"
	@ gcc -o $(NAME) $(LIB) $(OBJS)
	@ printf "$(PROJTEXT)\033[1;32mProgram built at $(NAME)\033[0;39m\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ if [ ! -z $@ ]; then mkdir -p $(dir $@); fi
	@ printf "\033[K$(PROJTEXT)Compiling \033[1;33m$<\033[0;39m\r"
	@ gcc $(CFLAGS) -c $< $(INCLUDES) -o $@

clean:
	@ make clean -C $(dir $(LIBFT))
	@ rm -rf $(OBJDIR)
	@ printf "$(PROJTEXT)Removed objects\n"

fclean: clean
	@ make fclean -C $(dir $(LIBFT))
	@ rm -f $(NAME)
	@ printf "$(PROJTEXT)Removed $(NAME)\n"

re: fclean all

.PHONY: all lib clean fclean re

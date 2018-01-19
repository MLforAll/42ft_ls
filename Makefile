# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/20 21:41:19 by kdumarai          #+#    #+#              #
#    Updated: 2018/01/19 05:44:47 by kdumarai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC_FLAGS = -Wall -Werror -Wextra
CC_LIB = -L libft -lft

LIBFT = libft/libft.a
INCLUDES = -I includes -I libft

SRCDIR = srcs
SRCFILES = ft_ls.c \
	ls_args.c \
	ls_colors.c \
	ls_misc.c \
	info/ls_getchars.c \
	info/ls_get_properties.c \
	info/ls_fill_properties.c \
	info/ls_start.c \
	sort/ls_sorting_comps.c \
	sort/ls_sorting_routine.c \
	display/ls_print_lst.c \
	display/ls_print_size.c \
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

all: $(NAME)



$(NAME): $(OBJS)
	@ printf "\r\033[K$(PROJTEXT)Compiling\n"
	@ make -C $(dir $(LIBFT))
	@ printf "$(PROJTEXT)Linking\n"
	@ gcc -o $(NAME) $(CC_LIB) $(OBJS)
	@ printf "$(PROJTEXT)\033[1;32mProgram built at $(NAME)\033[0;39m\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	@ printf "\033[K$(PROJTEXT)Compiling \033[1;33m$<\033[0;39m\r"
	@ gcc $(CC_FLAGS) -c $< $(INCLUDES) -o $@

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

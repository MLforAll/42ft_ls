#!/bin/sh
gflags="-Wall -Werror -Wextra"
if [ "$1" == "nf" ]; then
	gflags=""
fi
gcc $gflags -o ft_ls `find srcs -type f -name "*.c"` /Users/kdumarai/Documents/42_main_cursus/Libft/libft.a -I includes -I /Users/kdumarai/Documents/42_main_cursus/Libft

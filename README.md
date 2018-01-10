# 42ft_ls
42 School's ft_ls project

# This project aims to create a small replica of the \*nix command line tool `ls`

Currently Implemented:

- Listing of multiple folders and/or groups of files
- Option parsing (i.e: -laR || -l -a -R)
- Color Parsing with env var (LSCOLORS)
- Long printing (-l) with proper columns alignment
- Recursiveness (-R)
- Proper Makefile

TODO:

- Norming
- Opti: Freeing what's already malloced when unexpected fails of malloc
- Opti: Names of structs and fcts
- Opti: Sorting algorithm
- Opti: setup get_dir_content and such fcts to be usable as-is in libft

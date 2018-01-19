# 42ft_ls
42 School's ft_ls project

# This project aims to create a small replica of the \*nix command line tool `ls`

Currently Implemented:

- Listing of multiple folders and/or groups of files
- Option parsing (i.e: -laR || -l -a -R)
- Color Parsing with env var (LSCOLORS)
- Long printing (-l) with proper columns alignment
- Columns when -l is not spec
- Recursiveness (-R)
- Proper Makefile

Supported Flags:

-l (long format)
-a (show all)
-r (reverse sort)
-R (recursive search)
-t (sort by mod time)

Bonus Flags:

-s (show blocks for each file)
-F (show char after filename dep on file type)
-G (colors, assumed if CLICOLORS is set)
-1 (show one file per line in non long)
-@ (show extended attributes entires and data size)
-h (human format for sizes)
-n (force displaying user and group ID in numeric form)

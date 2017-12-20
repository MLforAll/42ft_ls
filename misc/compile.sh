#!/bin/sh
gcc components_tests.c ../srcs/ls_lst_sort.c ../srcs/ls_get_properties.c ../srcs/t_list_mgmt.c -I ../includes -I ../../Libft ../../Libft/libft.a -DSORT -o test

#!/bin/sh

echo "\033[1;39mPart0: Getting values\033[0;39m"
args=$@
echo "-> ls"
orig=$(/bin/ls $args)
orig_err=$?
[ $orig_err -gt 0 ] && printf \\n
echo "-> ft_ls"
mine=$(./ft_ls $args)
mine_err=$?

printf \\n
echo "\033[1;39mPart1: Output\033[0;39m"
echo "$mine" > /tmp/ls_mine.txt
echo "$orig" > /tmp/ls_orig.txt
diffres=$(diff -U 3 /tmp/ls_mine.txt /tmp/ls_orig.txt)
if [ -z "$diffres" ]; then
	echo "\033[1;32mDiff OK :D\033[0;39m"
	rm /tmp/ls_mine.txt /tmp/ls_orig.txt
else
	echo "\033[1;31mDiff KO :(\033[0;39m"
	printf \\n
	echo "ft_ls:"
	echo "$mine"
	printf \\n
	echo "------"
	printf \\n
	echo "ls:"
	echo "$orig"
	printf \\n
	echo "\033[1;31mValues can be retrived in /private/tmp dir!"
	echo "Don't forget to run /bin/ls and ./ft_ls side by side manually!\033[0;39m"
fi

printf \\n
echo "\033[1;39mPart2: Return value\033[0;39m"
if [ $mine_err -ne $orig_err ]; then
	echo "\033[1;31mReturn values are different! :(\033[0;39m"
	printf \\n
	echo "ft_ls: $mine_err"
	echo "ls   : $orig_err"
else
	echo "\033[1;32mRetval OK :D\033[0;39m"
fi

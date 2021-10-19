#!/bin/bash
file1="lala"
file2="lili"
gcc -Wall -Wextra -Werror -D TEST0 get_next_line.c get_next_line_utils.c
echo "reading from file1:"
valgrind ./a.out $file1
gcc -Wall -Wextra -Werror -D TEST1 get_next_line.c get_next_line_utils.c
echo "reading kbd input:"
echo "please type some input (ctrl D) to end"
valgrind ./a.out 
gcc -Wall -Wextra -Werror -D TEST2 get_next_line.c get_next_line_utils.c
echo "reading 3 from file1 and then file2"
valgrind ./a.out $file1 $file2
gcc -Wall -Wextra -Werror -D TEST0 get_next_line_bonus.c get_next_line_utils_bonus.c
echo "(bonus) reading from file1:"
valgrind ./a.out $file1
gcc -Wall -Wextra -Werror -D TEST1 get_next_line_bonus.c get_next_line_utils_bonus.c
echo "alternate kbd input and file1:"
echo "please type some input (ctrl D) to end"
valgrind ./a.out $file1


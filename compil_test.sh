#!/bin/sh
gcc -o test0 tests/test0.c
gcc -o test1 tests/test1.c -L. -lft_malloc -I includes
gcc -o test2 tests/test2.c -L. -lft_malloc -I includes
gcc -o test3-1 tests/test3-1.c -L. -lft_malloc -I includes
gcc -o test3-2 tests/test3-2.c -L. -lft_malloc -I includes
gcc -o test4 tests/test4.c -L. -lft_malloc -I includes
gcc -o test5 tests/test5.c -L. -lft_malloc -I includes
gcc -o test6 tests/test6.c -L. -lft_malloc -I includes

#!/bin/sh
gcc -o test0 tests/test0.c
gcc -o test1_os_malloc tests/test1.c
gcc -o test1_my_malloc tests/test1.c -L. -lft_malloc -I includes

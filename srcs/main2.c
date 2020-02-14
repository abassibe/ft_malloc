#include "../includes/ft_malloc.h"
#include <stdio.h>

int main()
{
    ft_malloc(10);
    ft_malloc(94);
    ft_malloc(1024);
    ft_malloc(1024);
    ft_malloc(1024 * 32);
    ft_malloc(1024 * 1024);
    ft_malloc(1024 * 1024 * 16);
    ft_malloc(1024 * 1024 * 128);
    malloc_dump(0);

    show_alloc_mem();
    return (0);
}
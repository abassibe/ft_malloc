#include "../includes/malloc.h"
#include <stdio.h>

int main()
{
    char *str;

    setenv("MallocHelp", "1", 1);
    str = malloc(12);
    str = malloc(10);
    str = malloc(94);
    str = malloc(1024);
    str = malloc(1024);
    str = malloc(1024 * 32);
    str = malloc(1024 * 1024);
    str = malloc(1024 * 1024 * 16);
    str = malloc(1024 * 1024 * 128);
    // malloc_dump();
    malloc_stats();

    show_alloc_mem();
    return (0);
}
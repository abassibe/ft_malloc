#include "../includes/malloc.h"
#include <stdio.h>

int main()
{
    setenv("MallocHelp", "1", 1);
    char *s = malloc(12);
    malloc(10);
    malloc(94);
    malloc(1024);
    malloc(1024);
    malloc(1024 * 32);
    malloc(1024 * 1024);
    malloc(1024 * 1024 * 16);
    malloc(1024 * 1024 * 128);
    malloc_dump();

    show_alloc_mem();
    return (0);
}
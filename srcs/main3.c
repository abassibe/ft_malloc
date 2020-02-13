#include "../includes/ft_malloc.h"
#include <stdio.h>

int main()
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char *)ft_malloc(1024);
        addr[0] = 42;
        ft_free(addr);
        i++;
    }
    return (0);
}
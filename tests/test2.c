/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:46:37 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/18 16:14:23 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/malloc.h"

int main()
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char *)malloc(1024);
        addr[0] = 42;
        free(addr);
        i++;
    }
    t_header *data;
    data = get_struct();
    i = 0;
    while (data)
    {
        data = data->next_zone;
        i++;
    }
    //show_alloc_mem();
    //malloc_dump();
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3-1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:24:35 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/19 13:24:55 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/malloc.h"

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{
    char *addr1;
    char *addr3;

    addr1 = (char *)malloc(16 * M);
    strcpy(addr1, "Bonjour\n");
    print(addr1);
    addr3 = (char *)realloc(addr1, 128 * M);
    addr3[127 * M] = 42;
    print(addr3);
    return (0);
}

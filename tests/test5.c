/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:46:39 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/19 13:48:23 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/malloc.h"

int main()
{
    char *str;

    str = malloc(1024);
    str = malloc(1024 * 32);
    str = malloc(1024 * 1024);
    str = malloc(1024 * 1024 * 16);
    str = malloc(1024 * 1024 * 128);
    show_alloc_mem();
    return (0);
}

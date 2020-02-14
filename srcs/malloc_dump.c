/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:30:57 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/13 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static void print_large(t_header *g_data, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        if (i < sizeof(t_header))
            ft_printf("\033[0;31m% 3.2x", ((unsigned char *)g_data)[i]);
        else if (i < sizeof(t_header) + sizeof(t_meta_data))
            ft_printf("\033[0;33m% 3.2x", ((unsigned char *)g_data)[i]);
        else
            ft_printf("\033[0;32m% 3.2x", ((unsigned char *)g_data)[i]);
        if (i > 0 && (i + 1) % 4 == 0)
            write(1, " ", 1);
        if (i > 0 && ((i + 1) % 32 == 0))
            write(1, "\n", 1);
        i++;
    }
    ft_printf("\033[0;0m\nPress enter to continue to the next page...\n");
    getchar();
}

static void print_tiny_small_next(t_meta_data *tmp, size_t len)
{
    int i;

    i = 0;
    while (tmp && i < len + sizeof(t_meta_data))
    {
        if (i < sizeof(t_meta_data))
            ft_printf("\033[0;33m% 3.2x", ((unsigned char *)tmp)[i]);
        else
            ft_printf("\033[0;32m% 3.2x", ((unsigned char *)tmp)[i]);
        if (i > 0 && (i + 1) % 4 == 0)
            write(1, " ", 1);
        if (i > 0 && ((i + 1) % 32 == 0))
            write(1, "\n", 1);
        i++;
        if (i >= len + sizeof(t_meta_data))
        {
            i = 0;
            write(1, "\n", 1);
            tmp = tmp->next;
        }
    }
}

static void print_tiny_small(t_header *g_data, size_t len)
{
    int i;

    i = 0;
    while (i < sizeof(t_header))
    {
        ft_printf("\033[0;31m% 3.2x", ((unsigned char *)g_data)[i]);
        if (i > 0 && (i + 1) % 4 == 0)
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
    print_tiny_small_next(g_data->first_elem, len);
    ft_printf("\033[0;0m\nPress enter to continue to the next page...\n");
    getchar();
}

static void print(t_header *g_data)
{
    int len;
    int page_count;

    page_count = 1;
    while (g_data)
    {
        ft_printf("PAGE #%d :\n", page_count);
        if (g_data->type == LARGE)
        {
            len = g_data->first_elem->size + sizeof(t_header) + sizeof(t_meta_data);
            print_large(g_data, len);
        }
        else if (g_data->type == SMALL)
            print_tiny_small(g_data, MAX_SMALL_SIZE);
        else
            print_tiny_small(g_data, MAX_TINY_SIZE);
        g_data = g_data->next_zone;
        page_count++;
    }
}

/* Print memory allocated with malloc.
Flag 0 : print all memory allocated.
Flag 1 : print without block's header.
Flag 2 : print without zone's header.
Flag 3 : print only user memory. */
void malloc_dump(int flag)
{
    t_header *g_data;

    g_data = get_struct();
    if (!g_data)
    {
        ft_printf("No memory allocated yet\n");
        return;
    }
    ft_printf("\033[0;31mZone's header\n");
    ft_printf("\033[0;33mBlock's header\n");
    ft_printf("\033[0;32mUser memory allocated\n");
    ft_printf("\033[0;0m");
    print(g_data);
}
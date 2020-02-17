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
        if (i % 32 == 0)
            ft_printf("\033[0;0m%p ", &((unsigned char *)g_data)[i]);
        if (i < sizeof(t_header))
            ft_printf("\033[0;31m% 3.2x", ((unsigned char *)g_data)[i]);
        else if (i < sizeof(t_header) + sizeof(t_meta_data))
            ft_printf("\033[0;33m% 3.2x", ((unsigned char *)g_data)[i]);
        else if ((!g_debug.malloc_do_not_protect_prelude && g_debug.malloc_guard_edges && i < sizeof(t_header) + sizeof(t_meta_data) + getpagesize()) ||
                 (!g_debug.malloc_do_not_protect_postlude && g_debug.malloc_guard_edges && i > len - getpagesize()))
            ft_printf("\033[1;31m% 3.2x", ((unsigned char *)g_data)[i]);
        else
            ft_printf("\033[0;32m% 3.2x", ((unsigned char *)g_data)[i]);
        if (i > 0 && i + 1 < len && (i + 1) % 4 == 0)
            write(1, " ", 1);
        if (i > 0 && i + 1 < len && ((i + 1) % 32 == 0))
            write(1, "\n", 1);
        i++;
    }
}

static void print_tiny_small_next(t_meta_data *tmp, size_t len)
{
    int i;

    i = 0;
    while (tmp && i < len + sizeof(t_meta_data))
    {
        if (i % 32 == 0)
            ft_printf("\033[0;0m%p ", &((unsigned char *)tmp)[i]);
        if (i < sizeof(t_meta_data))
            ft_printf("\033[0;33m% 3.2x", ((unsigned char *)tmp)[i]);
        else
            ft_printf("\033[0;32m% 3.2x", ((unsigned char *)tmp)[i]);
        if (i > 0 && i + 1 < len && (i + 1) % 4 == 0)
            write(1, " ", 1);
        if (i > 0 && i + 1 < len && ((i + 1) % 32 == 0))
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
        if (i % 32 == 0)
            ft_printf("\033[0;0m%p ", &((unsigned char *)g_data)[i]);
        ft_printf("\033[0;31m% 3.2x", ((unsigned char *)g_data)[i]);
        if (i > 0 && i + 1 < len && (i + 1) % 4 == 0)
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
    print_tiny_small_next(g_data->first_elem, len);
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
        ft_printf("\033[0;0m\nPress enter to continue to the next page...\n");
        getchar();
    }
}

void malloc_dump(void)
{
    t_header *g_data;

    g_data = get_struct();
    if (!g_data)
    {
        print_error("No allocation yet.\n", 0, NULL);
        return;
    }
    ft_printf("---INFOS---\n");
    ft_printf("\033[0;31mZone's header\n");
    ft_printf("\033[0;33mBlock's header\n");
    ft_printf("\033[0;32mUser memory allocated\n");
    ft_printf("\033[1;31mGuard page\n");
    ft_printf("\033[0;0m");
    ft_printf("-----------\n\n");
    pthread_mutex_lock(&g_mutex);
    print(g_data);
    pthread_mutex_unlock(&g_mutex);
}
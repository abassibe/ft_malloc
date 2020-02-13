/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:13:07 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static int is_all_free(t_meta_data *elem)
{
    while (elem)
    {
        if (elem->free == 0)
            return (0);
        elem = elem->next;
    }
    return (1);
}

void free_large_zone(t_header *g_data, t_header *preview, void *ptr)
{
    if (!g_data->next_zone)
        preview->next_zone = NULL;
    else
        preview->next_zone = g_data->next_zone;
    munmap(ptr, g_data->first_elem->size + sizeof(t_header) + sizeof(t_meta_data));
    return;
}

void free_tiny_small_zone(t_header *g_data, t_header *preview, t_meta_data *tmp, void *ptr)
{
    int size_to_free;

    tmp->free = 1;
    if (is_all_free(g_data->first_elem))
    {
        if (!g_data->next_zone)
            preview->next_zone = NULL;
        else
            preview->next_zone = g_data->next_zone;
        size_to_free = g_data->type == TINY ? MAX_TINY_ZONE : MAX_SMALL_ZONE;
        munmap(ptr, size_to_free);
    }
    return;
}

static void search_targeted_address(t_header *g_data, void *ptr)
{
    t_header *preview;
    t_meta_data *tmp;

    preview = g_data;
    while (g_data)
    {
        tmp = g_data->first_elem;
        while (tmp)
        {
            if (g_data->type == LARGE && tmp->addr == ptr)
            {
                free_large_zone(g_data, preview, ptr);
                return;
            }
            else if (tmp->addr == ptr)
            {
                free_tiny_small_zone(g_data, preview, tmp, ptr);
                return;
            }
            tmp = tmp->next;
        }
        preview = g_data;
        g_data = g_data->next_zone;
    }
}

extern void ft_free(void *ptr)
{
    t_header *g_data;

    if (!ptr)
        return;
    g_data = get_struct();
    if (!g_data)
        return;
    search_targeted_address(g_data, ptr);
}
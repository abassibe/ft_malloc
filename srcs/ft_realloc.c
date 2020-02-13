/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:54:21 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static void search_targeted_address(t_header *g_data, void *ptr, size_t size)
{
    t_header *preview;
    t_meta_data *tmp;
    void *ret;

    preview = g_data;
    while (g_data)
    {
        tmp = g_data->first_elem;
        while (tmp)
        {
            if (g_data->type == LARGE && tmp->addr == ptr)
            {
                ret = ft_memcpy(ft_malloc(size), tmp->addr, size);
                free_large_zone(g_data, preview, ptr);
                return (ret);
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

extern void *realloc(void *ptr, size_t size)
{
    t_header *g_data;

    g_data = get_struct();
    if (!ptr || !g_data)
        return (ft_malloc(size));
    if (size <= 0)
        size = 1;
    search_targeted_address(g_data, ptr, size);
}
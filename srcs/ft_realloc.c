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

static void *realloc_large(t_header *g_data, t_meta_data *meta_data, t_header *preview, size_t size)
{
    void *ret;

    if (meta_data->size >= size)
        return (meta_data->addr);
    ret = ft_malloc(size);
    ret = ft_memcpy(ret, meta_data->addr, size);
    free_large_zone(g_data, preview, meta_data->addr);
    return (ret);
}

static void *realloc_tiny_small(t_header *g_data, t_meta_data *meta_data, t_header *preview, size_t size)
{
    void *ret;

    if ((g_data->type == SMALL && size <= MAX_SMALL_SIZE) || (g_data->type == TINY && size <= MAX_TINY_SIZE))
        return (meta_data->addr);
    ret = ft_malloc(size);
    ret = ft_memcpy(ret, meta_data->addr, size);
    free_tiny_small_zone(g_data, preview, meta_data, meta_data->addr);
    return (ret);
}

static void *search_targeted_address(t_header *g_data, void *ptr, size_t size)
{
    t_header *preview;
    t_meta_data *tmp;

    preview = g_data;
    while (g_data)
    {
        tmp = g_data->first_elem;
        while (tmp)
        {
            if (tmp->addr == ptr && g_data->type == LARGE)
                return (realloc_large(g_data, tmp, preview, size));
            else if (tmp->addr == ptr)
                return (realloc_tiny_small(g_data, tmp, preview, size));
            tmp = tmp->next;
        }
        preview = g_data;
        g_data = g_data->next_zone;
    }
    return (NULL);
}

extern void *ft_realloc(void *ptr, size_t size)
{
    t_header *g_data;

    g_data = get_struct();
    if (!ptr || !g_data)
        return (ft_malloc(size));
    if (size <= 0)
        size = 1;
    return (search_targeted_address(g_data, ptr, size));
}
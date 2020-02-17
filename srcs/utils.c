/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:30:40 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/13 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/* Retourn le type d'allocation */
t_page_type get_page_type(size_t size)
{
    if (size <= MAX_TINY_SIZE)
        return (TINY);
    else if (size <= MAX_SMALL_SIZE)
        return (SMALL);
    return (LARGE);
}

void init_meta_data(t_header *g_data, size_t size)
{
    t_meta_data *meta_data;

    meta_data = (t_meta_data *)((char *)g_data + sizeof(t_header));
    if (g_data->type == LARGE && g_debug.malloc_guard_edges)
        meta_data->addr = (void *)((char *)g_data + sizeof(t_meta_data) + sizeof(t_header) + getpagesize());
    meta_data->addr = (void *)((char *)g_data + sizeof(t_meta_data) + sizeof(t_header));
    meta_data->prev = NULL;
    meta_data->next = NULL;
    meta_data->size = size;
    meta_data->free = 0;
    g_data->first_elem = meta_data;
}

void malloc_stats()
{
    pthread_mutex_lock(&g_mutex);
    ft_printf("\n -- malloc stats--\n");
    ft_printf("\n total_mmap_size_allocated  : %lu", total_mmap_size_allocated);
    ft_printf("\n total_allocation_request   : %lu", total_allocation_request);
    ft_printf("\n total_free_request         : %lu", total_free_request);
    pthread_mutex_unlock(&g_mutex);
}

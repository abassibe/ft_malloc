/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_allocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/13 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_header **first_alloc(void)
{
    static t_header *data = NULL;

    return (&data);
}

t_header *get_struct(void)
{
    return (*first_alloc());
}

t_header *allocate_large(t_header *page, size_t size)
{
    int extra;

    extra = 0;
    if (g_debug.malloc_guard_edges)
        extra = getpagesize() * 2;
    if (g_debug.malloc_guard_edges && !g_debug.malloc_do_not_protect_postlude)
        extra -= getpagesize();
    if (g_debug.malloc_guard_edges && !g_debug.malloc_do_not_protect_prelude)
        extra -= getpagesize();
    page = mmap(0, size + sizeof(t_header) + sizeof(t_meta_data) + extra, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    return (page);
}

/* Initialise le header de la première allocation */
t_header *init_header(size_t size)
{
    t_page_type type;
    t_header *data;

    data = NULL;
    type = get_page_type(size);
    if (type == TINY)
        data = mmap(0, MAX_TINY_ZONE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    else if (type == SMALL)
        data = mmap(0, MAX_SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    else
        data = allocate_large(data, size);
    if (data == MAP_FAILED)
        return (print_error("Failing memory allocation.\n", 1, NULL));
    data->next_zone = NULL;
    data->type = type;
    init_meta_data(data, size);
    *first_alloc() = data;
    pthread_mutex_lock(&g_mutex);
    total_mmap_size_allocated += size;
    pthread_mutex_unlock(&g_mutex);
    return (data);
}

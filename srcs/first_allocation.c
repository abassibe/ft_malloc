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

#include "../includes/ft_malloc.h"

t_header **first_alloc(void)
{
    static t_header *g_data = NULL;

    return (&g_data);
}

t_header *get_struct(void)
{
    return (*first_alloc());
}

/* Initialise le header de la première allocation */
t_header *init_header(size_t size)
{
    t_page_type type;
    t_header *g_data;

    type = get_page_type(size);
    if (type == TINY)
        g_data = mmap(0, MAX_TINY_ZONE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    else if (type == SMALL)
        g_data = mmap(0, MAX_SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    else
        g_data = mmap(0, size + sizeof(t_header) + sizeof(t_meta_data), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (g_data == MAP_FAILED)
        return (NULL);
    g_data->next_zone = NULL;
    g_data->type = type;
    init_meta_data(g_data, size);
    *first_alloc() = g_data;
    total_mmap_size_allocated += size;
    return (g_data);
}

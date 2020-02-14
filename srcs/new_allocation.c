/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:32:12 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/13 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/* Alloue une nouvelle zone suivant le type d'allocation. */
t_header *new_zone(t_page_type type, size_t size)
{
    t_header *new_page;

    new_page = NULL;
    if (type == TINY)
        new_page = mmap(0, MAX_TINY_ZONE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    else if (type == SMALL)
        new_page = mmap(0, MAX_SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    else
        new_page = mmap(0, size + sizeof(t_header) + sizeof(t_meta_data), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (new_page == MAP_FAILED)
        return (NULL);
    new_page->next_zone = NULL;
    new_page->type = type;
    init_meta_data(new_page, size);
    total_mmap_size_allocated += size;
    return (new_page);
}

/* Search for empty space or freed block for the new allocation. Return index if found, -1 otherwise. */
int looking_for_place(t_meta_data *region, t_page_type type)
{
    int count;
    int max_alloc_by_zone;

    count = 0;
    max_alloc_by_zone = (type == TINY ? MAX_TINY_ZONE : MAX_SMALL_ZONE) / ((type == TINY ? MAX_TINY_SIZE : MAX_SMALL_SIZE) + sizeof(t_meta_data));
    if (type == LARGE)
        return (-1);
    while (count < max_alloc_by_zone)
    {
        if (!region || region->free == 1)
        {
            return (count);
        }
        region = region->next;
        count++;
    }
    return (-1);
}

t_meta_data *create_new_block(t_meta_data *current_block, size_t size)
{
    t_meta_data *new_block;
    int length;
    length = size <= MAX_TINY_SIZE ? MAX_TINY_SIZE : MAX_SMALL_SIZE;

    new_block = (t_meta_data *)((char *)current_block + (length + sizeof(t_meta_data)));
    new_block->addr = (void *)((char *)new_block + sizeof(t_meta_data));
    new_block->prev = current_block;
    new_block->next = NULL;
    new_block->size = size;
    new_block->free = 0;
    current_block->next = new_block;
    return (new_block->addr);
}

void *create_allocation(t_header *g_data, size_t size, t_page_type type)
{
    t_meta_data *current_block;
    int count;
    int max_alloc_by_zone;

    current_block = g_data->first_elem;
    count = 0;
    max_alloc_by_zone = (type == TINY ? MAX_TINY_ZONE : MAX_SMALL_ZONE) / ((type == TINY ? MAX_TINY_SIZE : MAX_SMALL_SIZE) + sizeof(t_meta_data));
    while (count < max_alloc_by_zone)
    {
        if (current_block->free == 1)
        {
            current_block->size = size;
            current_block->free = 0;
            return (current_block->addr);
        }
        if (!current_block->next)
            return (create_new_block(current_block, size));
        current_block = current_block->next;
        count++;
    }
    return (NULL);
}
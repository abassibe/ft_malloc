/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:32:12 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/27 04:25:54 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t	calculat_zone_size(int size)
{
	return (((((size + sizeof(t_meta_data)) * MIN_ALLOC_BY_ZONE) +
					sizeof(t_header)) / getpagesize()) + 1) * getpagesize();
}

t_header		*new_zone(t_page_type type, size_t size)
{
	t_header	*new_page;
	int			max_tiny_zone;
	int			max_small_zone;

	max_tiny_zone = calculat_zone_size(MAX_TINY_SIZE);
	max_small_zone = calculat_zone_size(MAX_SMALL_SIZE);
	new_page = NULL;
	if (type == TINY)
		new_page = mmap(0, max_tiny_zone, PROT_READ |
				PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (type == SMALL)
		new_page = mmap(0, max_small_zone, PROT_READ |
				PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else
		new_page = allocate_large(new_page, size);
	if (new_page == MAP_FAILED)
		return (print_error("", 1, NULL));
	new_page->next_zone = NULL;
	new_page->type = type;
	init_meta_data(new_page, size, type);
	pthread_mutex_lock(&g_mutex);
	g_total_mmap_size_allocated += size;
	pthread_mutex_unlock(&g_mutex);
	return (new_page);
}

int				looking_for_place(t_meta_data *region, t_page_type type)
{
	int		count;
	int		max_alloc_by_zone;
	int		max_tiny_zone;
	int		max_small_zone;

	max_tiny_zone = calculat_zone_size(MAX_TINY_SIZE);
	max_small_zone = calculat_zone_size(MAX_SMALL_SIZE);
	count = 0;
	max_alloc_by_zone = (type == TINY ? max_tiny_zone : max_small_zone) /
		((type == TINY ? MAX_TINY_SIZE : MAX_SMALL_SIZE) + sizeof(t_meta_data));
	if (type == LARGE)
		return (-1);
	while (count < max_alloc_by_zone)
	{
		if (!region || region->free == 1)
			return (count);
		region = region->next;
		count++;
	}
	return (-1);
}

t_meta_data		*create_new_block(t_meta_data *current_block, size_t size)
{
	t_meta_data	*new_block;
	int			length;

	length = size <= MAX_TINY_SIZE ? MAX_TINY_SIZE : MAX_SMALL_SIZE;
	new_block = (t_meta_data *)((char *)current_block +
			(length + sizeof(t_meta_data)));
	new_block->addr = (void *)((char *)new_block + sizeof(t_meta_data));
	new_block->prev = current_block;
	new_block->next = NULL;
	new_block->size = size;
	new_block->free = 0;
	current_block->next = new_block;
	return (new_block->addr);
}

void			*create_allocation(t_header *data, size_t size,
		t_page_type type)
{
	t_meta_data	*current_block;
	int			count;
	int			max_alloc_by_zone;
	int			max_tiny_zone;
	int			max_small_zone;

	max_tiny_zone = calculat_zone_size(MAX_TINY_SIZE);
	max_small_zone = calculat_zone_size(MAX_SMALL_SIZE);
	current_block = data->first_elem;
	count = -1;
	max_alloc_by_zone = (type == TINY ? max_tiny_zone : max_small_zone) /
		((type == TINY ? MAX_TINY_SIZE : MAX_SMALL_SIZE) + sizeof(t_meta_data));
	while (++count < max_alloc_by_zone)
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
	}
	return (NULL);
}

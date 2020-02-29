/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:32:12 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/29 07:02:41 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t				zone_size(int size)
{
	return (((((size + padding(sizeof(t_meta_data))) *
						MIN_ALLOC_BY_ZONE) + padding(sizeof(t_header))) /
				getpagesize()) + 1) * getpagesize();
}

t_header			*new_zone(t_page_type type, size_t size)
{
	t_header	*new_page;

	new_page = NULL;
	if (type == TINY)
		new_page = mmap(0, zone_size(MAX_TINY_SIZE),
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (type == SMALL)
		new_page = mmap(0, zone_size(MAX_SMALL_SIZE),
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
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

static t_meta_data	*create_new_block(t_meta_data *current_block,
		t_meta_data *next_block, size_t size)
{
	int		length;

	length = padding(size);
	next_block->addr = (void *)((char *)next_block +
			padding(sizeof(t_meta_data)));
	next_block->prev = current_block;
	next_block->next = NULL;
	next_block->size = size;
	next_block->free = 0;
	current_block->next = next_block;
	return (next_block->addr);
}

void				*looking_for_place(t_header *header, t_page_type type,
		size_t size)
{
	size_t			len;
	size_t			pc;
	t_meta_data		*r;

	r = header->first_elem;
	len = type == TINY ? zone_size(MAX_TINY_SIZE) : zone_size(MAX_SMALL_SIZE);
	while (type != LARGE && r)
	{
		if (r->free == 1 && padding(r->size) >= padding(size))
		{
			r->size = size;
			r->free = 0;
			return (r->addr);
		}
		if (!r->next)
		{
			pc = (int)(r->addr + padding(r->size)) - (int)header;
			if (pc + padding(sizeof(t_meta_data)) + padding(size) < len)
				return (create_new_block(r, r->addr + padding(r->size), size));
			return (NULL);
		}
		r = r->next;
	}
	return (NULL);
}

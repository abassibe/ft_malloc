/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_allocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/27 04:02:07 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/errno.h>

t_header	**first_alloc(void)
{
	static t_header	*data = NULL;

	return (&data);
}

t_header	*get_struct(void)
{
	return (*first_alloc());
}

t_header	*allocate_large(t_header *page, size_t size)
{
	int	extra;

	extra = 0;
	if (g_debug.guard_edges)
		extra = getpagesize() * 2;
	if (g_debug.guard_edges && !g_debug.do_not_protect_postlude)
		extra -= getpagesize();
	if (g_debug.guard_edges && !g_debug.do_not_protect_prelude)
		extra -= getpagesize();
	page = mmap(0, size + sizeof(t_header) + sizeof(t_meta_data) + extra,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (page);
}

t_header	*init_header(size_t size)
{
	t_page_type	type;
	t_header	*data;
	int			max_tiny_zone;
	int			max_small_zone;

	data = NULL;
	type = get_page_type(size);
	max_tiny_zone = (((((128 + sizeof(t_meta_data)) * MIN_ALLOC_BY_ZONE) +
					sizeof(t_header)) / getpagesize()) + 1) * getpagesize();
	max_small_zone = (((((1024 + sizeof(t_meta_data)) * MIN_ALLOC_BY_ZONE) +
					sizeof(t_header)) / getpagesize()) + 1) * getpagesize();
	if (type == TINY)
		data = mmap(0, max_tiny_zone,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (type == SMALL)
		data = mmap(0, max_small_zone,
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else
		data = allocate_large(data, size);
	init_meta_data(data, size, type);
	*first_alloc() = data;
	pthread_mutex_lock(&g_mutex);
	g_total_mmap_size_allocated += size;
	pthread_mutex_unlock(&g_mutex);
	return (data);
}

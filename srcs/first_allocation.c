/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_allocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/29 06:37:00 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/errno.h>

t_header	**first_alloc(void)
{
	static	t_header *data = NULL;

	g_debug.debug_report = NULL;
	g_debug.guard_edges = NULL;
	g_debug.do_not_protect_prelude = NULL;
	g_debug.do_not_protect_postlude = NULL;
	g_debug.error_abort = NULL;
	return (&data);
}

t_header	*get_struct(void)
{
	return (*first_alloc());
}

t_header	*allocate_large(t_header *page, size_t size)
{
	int		extra;

	extra = 0;
	if (g_debug.guard_edges)
		extra = getpagesize() * 2;
	if (g_debug.guard_edges && !g_debug.do_not_protect_postlude)
		extra -= getpagesize();
	if (g_debug.guard_edges && !g_debug.do_not_protect_prelude)
		extra -= getpagesize();
	page = mmap(0, padding(size) + padding(sizeof(t_header)) +
			padding(sizeof(t_meta_data)) + extra,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (page);
}

t_header	*init_header(size_t size)
{
	t_page_type		type;
	t_header		*data;

	data = NULL;
	type = get_page_type(size);
	if (type == TINY)
		data = mmap(0, calculat_zone_size(MAX_TINY_SIZE),
				PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (type == SMALL)
		data = mmap(0, calculat_zone_size(MAX_SMALL_SIZE),
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

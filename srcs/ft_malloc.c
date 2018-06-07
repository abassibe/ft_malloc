/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/07 04:07:40 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_header	g_data = {NULL, NULL, NULL, NULL, -1, 0};

void	malloc_small(void **addr, size_t size)
{
	*addr = mmap(NULL, SMALL_ZONE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	malloc_big(void **addr, size_t size)
{
	*addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	*first_alloc(void *addr, int size)
{
	char		map[512];

	if (size < MAX_TINY)
	{
		addr = mmap(NULL, TINY_ZONE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
		g_data.start = &addr[sizeof(t_header)];
		g_data.next = NULL;
		g_data.mapping = map;
		g_data.prev_addr = NULL;
		g_data.type = TINY;
		g_data.max_adjacent = 511 * 64;
		ft_memcpy(addr, &g_data, sizeof(t_header));
	}
	return (addr);
}

void	*malloc(size_t size)
{
	void	*addr;

	printf("test\n");
	if (!g_data.start)
		addr = first_alloc(addr, size);
	if (size < TINY)
		malloc_tiny(&addr, size);
	else if (size < SMALL)
		malloc_small(&addr, size);
	else
		malloc_big(&addr, size);
	g_data.next = (char *)addr;
	show_alloc_mem_better_than_show_alloc_mem();
	return (addr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_header	g_data = {NULL, NULL, NULL, {0}, NULL, -1, 0};

void	malloc_small(size_t size)
{
	void	*addr;

	addr = mmap(NULL, SMALL_ZONE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
}

void	malloc_big(size_t size)
{
	void	*addr;

	addr = mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
}

void	first_alloc(size_t size)
{
	void	*addr;

	if (size < MAX_TINY)
	{
		addr = mmap(NULL, TINY_ZONE, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		g_data.start = NULL;
		g_data.next = NULL;
		g_data.prev_addr = NULL;
		g_data.type = TINY;
		g_data.max_adjacent = 503 * 64; // valeur variable qui définit la taille maximale consécutive possible d'une allocation dans la zone/map
		addr = ft_memcpy(addr, &g_data, sizeof(t_header));
	}
	g_data.start_zone = &*addr;
}

void	*ft_malloc(size_t size)
{
	if (!g_data.start)
		first_alloc(size);
	if (size < MAX_TINY)
		malloc_tiny(size);
	else if (size < MAX_SMALL)
		malloc_small(size);
	else
		malloc_big(size);
	return (g_data.start_zone);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/05 04:28:00 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_meta_data		g_data = {NULL, 0, NULL, 0};

void	malloc_tiny(void **addr, size_t size)
{
	*addr = mmap(NULL, TINY_ZONE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	malloc_small(void **addr, size_t size)
{
	*addr = mmap(NULL, SMALL_ZONE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	malloc_big(void **addr, size_t size)
{
	*addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	*ft_malloc(size_t size)
{
	void	*addr;
	if (size < TINY)
		malloc_tiny(&addr, size);
	else if (size < SMALL)
		malloc_small(&addr, size);
	else
		malloc_big(&addr, size);
	printf("%lu\n", sizeof(g_data));
	return (addr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/06 05:05:07 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_header	*(g_data) = {NULL, NULL, NULL, NULL, -1, 0};

void	malloc_small(void **addr, size_t size)
{
	*addr = mmap(NULL, SMALL_ZONE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	malloc_big(void **addr, size_t size)
{
	*addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	*malloc(size_t size)
{
	void	*addr;
	if (!g_data->start)
		first_alloc(&addr, size);
	if (size < TINY)
		malloc_tiny(&addr, size);
	else if (size < SMALL)
		malloc_small(&addr, size);
	else
		malloc_big(&addr, size);
	printf("%lu\n", sizeof(t_header));
	return (addr);
}

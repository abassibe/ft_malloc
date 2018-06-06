/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/07 01:34:53 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_header	*g_data = NULL;

void	malloc_small(void **addr, size_t size)
{
	*addr = mmap(NULL, SMALL_ZONE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

void	malloc_big(void **addr, size_t size)
{
	*addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

char	*first_alloc(int size)
{
	char	str[3] = "dfg";
	char *cpy  = str;
	t_header	*tmp;
	tmp->start = NULL;
	tmp->next = NULL;
	tmp->mapping = "YAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH";
	tmp->prev_addr = NULL;
	tmp->type = -1;
	tmp->max_adjacent = 0;

	printf("%p\n", cpy);
//	g_data = tmp;
	return (cpy);
}

void	*malloc(size_t size)
{
	void	*addr;
	char	*tmp;

	if (!g_data)
		tmp = first_alloc(size);
	if (size < TINY)
		malloc_tiny(&addr, size);
	else if (size < SMALL)
		malloc_small(&addr, size);
	else
		malloc_big(&addr, size);
	write(1, "por\n", 4);
	return (addr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 04:04:57 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/07 01:31:26 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	malloc_tiny(void **addr, size_t size)
{
	t_header	*tmp;
/*	tmp = g_data;
	while (tmp->next && tmp->type != 0)
		tmp = tmp->next;
	if (tmp->type == 0 && tmp->max_adjacent > size + sizeof(t_meta_data))
		allocate_cluster(addr, size, TINY_CLUSTER);
	else
		allocate_zone(addr, size, TINY_ZONE);*/
//	*addr = mmap(NULL, TINY_ZONE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 03:44:19 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 03:39:53 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	print_tiny(t_header tmp, size_t size)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < size)
	{
		if (j % 64 == 0 && j > 0)
		{
			write(1, "\n", 1);
			j = 0;
		}
		else if (j % 8 == 0 && j > 0)
			write(1, " ", 1);
		if (((char *)tmp.start_zone)[i] > 31 && ((char *)tmp.start_zone)[i] < 127)
			write(1, &((char *)tmp.start_zone)[i], 1);
		else
			write(1, ".", 1);
		j++;
	}
	write(1, "\n", 1);
}

void	show_alloc_mem_better_than_show_alloc_mem()
{
	t_header	*tmp;

	tmp = &g_data;
	while (tmp)
	{
		if (tmp->type == TINY)
		{
			printf("Tiny map :\n");
			print_tiny(*tmp, TINY_ZONE);
		}
		else if (tmp->type == SMALL)
		{
			ft_printf("Small map :\n");
//			print_small(&tmp);
		}
		else
		{
			ft_printf("Large map :\n");
//			print_large(&tmp);
		}
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////\n");
		tmp = tmp->next;
	}
}

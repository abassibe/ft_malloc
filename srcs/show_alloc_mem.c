/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 03:44:19 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/07 04:10:13 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	print_tiny(t_header *tmp)
{
	int		i;

	i = -1;
	while (++i < TINY_ZONE)
	{
		if (tmp->next[i] > 31 && tmp->next[i] < 127)
			write(1, &tmp->next[i], 1);
		else
			ft_printf("%d\n", tmp->next[i]);
	}
}

void	show_alloc_mem_better_than_show_alloc_mem()
{
	t_header	tmp;

	printf("dfgdfh\n");
	tmp = g_data;
	while (tmp.next)
	{
		if (tmp.type == TINY)
		{
			ft_printf("Tiny map :\n");
			print_tiny(&tmp);
		}
		else if (tmp.type == SMALL)
		{
			ft_printf("Small map :\n");
//			print_small(&tmp);
		}
		else
		{
			ft_printf("Large map :\n");
//			print_large(&tmp);
		}
	}
}

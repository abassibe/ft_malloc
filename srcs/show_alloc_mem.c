/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 03:44:19 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 03:39:53 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static void fill_tab(t_header **tab, t_header *g_data)
{
	int i;

	i = 0;
	while (g_data)
	{
		tab[i] = g_data;
		g_data = g_data->next_zone;
		i++;
	}
	tab[i] = NULL;
}

static void print(t_header **tab)
{
	int i;
	int total;
	t_meta_data *tmp;

	i = 0;
	total = 0;
	while (tab[i])
	{
		if (tab[i]->type == TINY)
			ft_printf("TINY : %p\n", tab[i]);
		else if (tab[i]->type == SMALL)
			ft_printf("SMALL : %p\n", tab[i]);
		else
			ft_printf("LARGE : %p\n", tab[i]);
		tmp = tab[i]->first_elem;
		while (tmp)
		{
			ft_printf("%p - %p : %lu octets\n", tmp->addr, tmp->addr + tmp->size, tmp->size);
			total += tmp->size;
			tmp = tmp->next;
		}
		i++;
	}
	ft_printf("Total : %d octets\n", total);
}

static void sort_by_address(t_header *g_data, int amount_of_zone)
{
	t_header *tmp;
	t_header *tab[amount_of_zone + 1];
	int i;

	i = 0;
	fill_tab(tab, g_data);
	while (amount_of_zone > 0)
	{
		if (i < amount_of_zone && tab[i + 1] && (&*tab[i] > &*tab[i + 1]))
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
		}
		if (i >= amount_of_zone)
		{
			amount_of_zone--;
			i = 0;
		}
		i++;
	}
	print(tab);
}

static int count_zone(t_header *g_data)
{
	int i;

	i = 0;
	while (g_data)
	{
		g_data = g_data->next_zone;
		i++;
	}
	return (i);
}

extern void show_alloc_mem()
{
	t_header *g_data;

	g_data = get_struct();
	if (!g_data)
	{
		print_error("No allocation yet.\n", 0, NULL);
		return;
	}
	pthread_mutex_lock(&g_mutex);
	sort_by_address(g_data, count_zone(g_data));
	pthread_mutex_unlock(&g_mutex);
}
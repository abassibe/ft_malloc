/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 03:44:19 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/27 01:26:48 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	fill_tab(t_header **tab, t_header *data)
{
	int	i;

	i = 0;
	while (data)
	{
		tab[i] = data;
		data = data->next_zone;
		i++;
	}
	tab[i] = NULL;
}

static int	print(t_header **tab)
{
	int			total;
	t_meta_data	*tmp;

	total = 0;
	while (*tab)
	{
		if ((*tab)->type == TINY)
			write(1, "TINY : ", 7);
		else if ((*tab)->type == SMALL)
			write(1, "SMALL : ", 7);
		else
			write(1, "LARGE : ", 7);
		print_address((unsigned long)*tab);
		write(1, "\n", 1);
		tmp = (*tab)->first_elem;
		while (tmp)
		{
			total += print_bloc_address(tmp);
			tmp = tmp->next;
		}
		tab++;
	}
	return (total);
}

static void	sort_by_address(t_header *data, int amount_of_zone)
{
	t_header	*tmp;
	t_header	*tab[amount_of_zone + 1];
	int			i;

	i = 0;
	fill_tab(tab, data);
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
	i = print(tab);
	write(1, "Total : ", 8);
	ft_putnbr(i);
	write(1, " octets\n", 8);
}

static int	count_zone(t_header *data)
{
	int	i;

	i = 0;
	while (data)
	{
		data = data->next_zone;
		i++;
	}
	return (i);
}

void		show_alloc_mem(void)
{
	t_header	*data;

	data = get_struct();
	if (!data)
	{
		print_error("", 0, NULL);
		return ;
	}
	pthread_mutex_lock(&g_mutex);
	sort_by_address(data, count_zone(data));
	pthread_mutex_unlock(&g_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:30:57 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/29 06:37:51 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	print_large(t_header *data, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (i % 32 == 0)
			print_address((unsigned long)&((unsigned char *)data)[i]);
		if (i < sizeof(t_header))
			useless_layer(((unsigned char *)data)[i], "\033[0;31m");
		else if (i < sizeof(t_header) + sizeof(t_meta_data))
			useless_layer(((unsigned char *)data)[i], "\033[0;33m");
		else if ((!g_debug.do_not_protect_prelude && g_debug.guard_edges &&
					i < sizeof(t_header) + sizeof(t_meta_data) + getpagesize())
				|| (!g_debug.do_not_protect_postlude && g_debug.guard_edges &&
					i > len - getpagesize()))
			useless_layer(((unsigned char *)data)[i], "\033[0;31m");
		else
			useless_layer(((unsigned char *)data)[i], "\033[0;32m");
		if (i > 0 && i + 1 < len && (i + 1) % 4 == 0)
			write(1, " ", 1);
		if (i > 0 && i + 1 < len && ((i + 1) % 32 == 0))
			write(1, "\n", 1);
		i++;
	}
}

static void	print_tiny_small_next(t_meta_data *tmp, size_t len)
{
	size_t	i;

	i = 0;
	while (tmp && i < len + sizeof(t_meta_data))
	{
		if (i % 32 == 0)
			print_address((unsigned long)&((unsigned char *)tmp)[i]);
		if (i < sizeof(t_meta_data))
			useless_layer(((unsigned char *)tmp)[i], "\033[0;33m");
		else
			useless_layer(((unsigned char *)tmp)[i], "\033[0;32m");
		if (i > 0 && i + 1 < len + sizeof(t_meta_data) && (i + 1) % 4 == 0)
			write(1, " ", 1);
		if (i > 0 && i + 1 < len + sizeof(t_meta_data) && ((i + 1) % 32 == 0))
			write(1, "\033[0;0m\n", 7);
		i++;
		if (i >= len + sizeof(t_meta_data))
		{
			i = 0;
			write(1, "\033[0;0m\n", 7);
			tmp = tmp->next;
		}
	}
}

static void	print_tiny_small(t_header *data, size_t len)
{
	size_t	i;

	i = 0;
	while (i < sizeof(t_header))
	{
		if (i % 32 == 0)
			print_address((unsigned long)&((unsigned char *)data)[i]);
		useless_layer(((unsigned char *)data)[i], "\033[0;31m");
		if (i > 0 && i + 1 < len && (i + 1) % 4 == 0)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	print_tiny_small_next(data->first_elem, len);
}

static void	print(t_header *data)
{
	unsigned long	page_count;

	page_count = 1;
	while (data)
	{
		write(1, "PAGE #", 6);
		print_value(page_count);
		write(1, " :\n", 3);
		if (data->type == LARGE)
			print_large(data, data->first_elem->size + sizeof(t_header) +
					sizeof(t_meta_data));
		else if (data->type == SMALL)
			print_tiny_small(data, MAX_SMALL_SIZE);
		else
			print_tiny_small(data, MAX_TINY_SIZE);
		data = data->next_zone;
		page_count++;
		if (!data)
			break ;
		write(1, "\033[0;0m\nPress enter to continue to the next page..\n", 50);
		getchar();
	}
}

void		malloc_dump(void)
{
	t_header	*data;

	data = get_struct();
	if (!data)
	{
		print_error("No allocation yet.\n", 0, NULL);
		return ;
	}
	pthread_mutex_lock(&g_mutex);
	write(1, "---INFOS---\n", 12);
	write(1, "\033[0;31mHeader zone\n", 19);
	write(1, "\033[0;33mHeader block\n", 20);
	write(1, "\033[0;32mUser memory allocated\n", 29);
	write(1, "\033[1;31mGuard page\n", 18);
	write(1, "\033[0;0m-----------\n\n", 19);
	print(data);
	pthread_mutex_unlock(&g_mutex);
}

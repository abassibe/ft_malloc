/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:13:07 by abassibe          #+#    #+#             */
/*   Updated: 2020/03/11 11:48:19 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int		is_all_free(t_meta_data *elem)
{
	while (elem)
	{
		if (elem->free == 0)
			return (0);
		elem = elem->next;
	}
	return (1);
}

void			free_large_zone(t_header *data, t_header *preview)
{
	int		extra;

	extra = 0;
	if (data == preview)
		return ;
	if (!data->next_zone)
		preview->next_zone = NULL;
	else
		preview->next_zone = data->next_zone;
	if (g_debug.guard_edges)
		extra = getpagesize() * 2;
	if (g_debug.guard_edges && !g_debug.do_not_protect_postlude)
		extra -= getpagesize();
	if (g_debug.guard_edges && !g_debug.do_not_protect_prelude)
		extra -= getpagesize();
	munmap(data, data->first_elem->size + sizeof(t_header) +
			sizeof(t_meta_data) + extra);
	return ;
}

void			free_tiny_small_zone(t_header *data, t_header *preview,
		t_meta_data *tmp)
{
	int		size_to_free;

	tmp->free = 1;
	if (tmp->next && tmp->next->free)
	{
		tmp->size += padding(sizeof(t_meta_data)) + padding(tmp->next->size);
		tmp->next = tmp->next->next;
	}
	if (is_all_free(data->first_elem) && data != preview)
	{
		if (!data->next_zone)
			preview->next_zone = NULL;
		else
			preview->next_zone = data->next_zone;
		size_to_free = data->type == TINY ? zone_size(MAX_TINY_SIZE) :
			zone_size(MAX_SMALL_SIZE);
		munmap(data, size_to_free);
	}
	return ;
}

static void		search_targeted_address(t_header *data, void *ptr)
{
	t_header		*preview;
	t_meta_data		*tmp;

	preview = data;
	while (data)
	{
		tmp = data->first_elem;
		while (tmp)
		{
			if (tmp->addr == ptr)
			{
				if (data->type == LARGE)
					free_large_zone(data, preview);
				else
					free_tiny_small_zone(data, preview, tmp);
				return ;
			}
			tmp = tmp->next;
		}
		preview = data;
		data = data->next_zone;
	}
	print_error("", 0, NULL);
}

void			free(void *ptr)
{
	t_header	*data;

	pthread_mutex_lock(&g_mutex);
	g_total_free_request++;
	if (!ptr)
	{
		print_error("", 0, NULL);
		return ;
	}
	data = get_struct();
	if (!data)
	{
		print_error("", 0, NULL);
		return ;
	}
	search_targeted_address(data, ptr);
	pthread_mutex_unlock(&g_mutex);
}

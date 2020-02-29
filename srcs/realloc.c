/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:54:21 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/29 06:50:11 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*realloc_large(t_header *data, t_meta_data *block,
		t_header *preview, size_t size)
{
	void	*ret;
	size_t	to_copy;

	if (padding(size) <= padding(block->size))
		return (block->addr);
	ret = malloc(size);
	to_copy = block->size < size ? block->size : size;
	ret = ft_memcpy(ret, block->addr, to_copy);
	free_large_zone(data, preview);
	return (ret);
}

static void		*realloc_tiny_small(t_header *data, t_meta_data *block,
		t_header *preview, size_t size)
{
	void	*ret;
	size_t	to_copy;

	if (padding(size) == padding(block->size))
		return (block->addr);
	ret = malloc(size);
	to_copy = block->size < size ? block->size : size;
	ret = ft_memcpy(ret, block->addr, to_copy);
	free_tiny_small_zone(data, preview, block);
	return (ret);
}

static void		*search_targeted_address(t_header *data, void *ptr, size_t size)
{
	t_header		*preview;
	t_meta_data		*tmp;

	preview = data;
	while (data)
	{
		tmp = data->first_elem;
		while (tmp)
		{
			if (tmp->addr == ptr && data->type == LARGE)
				return (realloc_large(data, tmp, preview, size));
			else if (tmp->addr == ptr && (data->type == TINY ||
						data->type == SMALL))
				return (realloc_tiny_small(data, tmp, preview, size));
			tmp = tmp->next;
		}
		preview = data;
		data = data->next_zone;
	}
	print_error("", 1, NULL);
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	t_header	*data;
	void		*ret;

	pthread_mutex_lock(&g_mutex);
	data = get_struct();
	if (!ptr || !data)
		return (malloc(size));
	if (size <= 0)
		size = 1;
	ret = search_targeted_address(data, ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

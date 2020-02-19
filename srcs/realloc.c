/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:54:21 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void *realloc_large(t_header *data, t_meta_data *meta_data, t_header *preview, size_t size)
{
    void *ret;

    if (meta_data->size >= size)
        return (meta_data->addr);
    ret = malloc(size);
    ret = ft_memcpy(ret, meta_data->addr, meta_data->size);
    free_large_zone(data, preview);
    return (ret);
}

static void *realloc_tiny_small(t_header *data, t_meta_data *meta_data, t_header *preview, size_t size)
{
    void *ret;

    if ((data->type == SMALL && size <= MAX_SMALL_SIZE) || (data->type == TINY && size <= MAX_TINY_SIZE))
        return (meta_data->addr);
    ret = malloc(size);
    ret = ft_memcpy(ret, meta_data->addr, size);
    free_tiny_small_zone(data, preview, meta_data);
    return (ret);
}

static void *search_targeted_address(t_header *data, void *ptr, size_t size)
{
    t_header *preview;
    t_meta_data *tmp;

    preview = data;
    while (data)
    {
        tmp = data->first_elem;
        while (tmp)
        {
            if (tmp->addr == ptr && data->type == LARGE)
                return (realloc_large(data, tmp, preview, size));
            else if (tmp->addr == ptr)
                return (realloc_tiny_small(data, tmp, preview, size));
            tmp = tmp->next;
        }
        preview = data;
        data = data->next_zone;
    }
    print_error("", 1, NULL);
    return (NULL);
}

void *realloc(void *ptr, size_t size)
{
    t_header *data;
    void *ret;

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:30:40 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/13 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int print_bloc_address(t_meta_data *tmp)
{
    print_address((unsigned long)tmp->addr);
    write(1, " - ", 3);
    print_address((unsigned long)tmp->addr + tmp->size);
    write(1, " : ", 3);
    ft_putnbr((int)tmp->size);
    write(1, " octets\n", 8);
    return (tmp->size);
}

t_page_type get_page_type(size_t size)
{
    if (size <= MAX_TINY_SIZE)
        return (TINY);
    else if (size <= MAX_SMALL_SIZE)
        return (SMALL);
    return (LARGE);
}

void init_meta_data(t_header *data, size_t size)
{
    t_meta_data *meta_data;

    meta_data = (t_meta_data *)((char *)data + sizeof(t_header));
    if (data->type == LARGE && g_debug.malloc_guard_edges)
        meta_data->addr = (void *)((char *)data + sizeof(t_meta_data) + sizeof(t_header) + getpagesize());
    meta_data->addr = (void *)((char *)data + sizeof(t_meta_data) + sizeof(t_header));
    meta_data->prev = NULL;
    meta_data->next = NULL;
    meta_data->size = size;
    meta_data->free = 0;
    data->first_elem = meta_data;
}

void malloc_stats(void)
{
    pthread_mutex_lock(&g_mutex);
    write(1, "\n-- malloc stats --\n", 20);
    write(1, "Total mmap size allocated : ", 28);
    if (total_mmap_size_allocated == 0)
        write(1, "0", 1);
    else
        print_value(total_mmap_size_allocated);
    write(1, "\n", 1);

    write(1, "Total allocation request  : ", 28);
    if (total_allocation_request == 0)
        write(1, "0", 1);
    else
        print_value(total_allocation_request);
    write(1, "\n", 1);

    write(1, "Total free request        : ", 28);
    if (total_free_request == 0)
        write(1, "0", 1);
    else
        print_value(total_free_request);
    write(1, "\n", 1);
    pthread_mutex_unlock(&g_mutex);
}

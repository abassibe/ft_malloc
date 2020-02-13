/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/* En cas de nouvelle allocation, vérifie l'existence d'une zone et la place par type. Réoriente au besoin. */
static void *new_allocation(t_header *g_data, size_t size)
{
	t_header *header;
	t_page_type type;

	type = get_page_type(size);
	header = g_data;
	while (header)
	{
		if (header->type == type && looking_for_place(header->first_elem, type) != -1)
			return (create_allocation(header, size, type));
		if (!header->next_zone)
			break;
		header = header->next_zone;
	}
	header->next_zone = new_zone(type, size);
	return (header->next_zone->first_elem->addr);
}

/* Renvoie un pointeur sur une zone mémoire allouée de size octet */
extern void *ft_malloc(size_t size)
{
	t_header *g_data;
	void *ret;

	if (size <= 0)
		return (NULL);
	g_data = get_struct();
	if (!g_data)
		return (&*init_header(size)->first_elem->addr);
	if (!(ret = new_allocation(g_data, size)))
		return (NULL);
	return (&*ret);
}

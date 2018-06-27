/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 04:04:57 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:14 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static inline char		check_mapping(int *iter, char *mapping, int nb_cluster)
{
	int				j;

	j = -1;
	if (mapping[*iter] == '0')
		while (++j < nb_cluster)
		{
			if (mapping[*iter] == '1')
				return (0);
			(*iter)++;
		}
	return (1);
}

void	search_next_meta(t_header *header, t_meta_data *start, t_meta_data new)
{
	while (start->next)
		start = start->next;
	start->next = ft_memcpy(header->start_zone + sizeof(t_header),
			&new, sizeof(t_meta_data));
}

void	create_meta_data_tiny(t_header *header, size_t size)
{
	t_meta_data		new;
	size_t			nb_cluster;
	int				i;

	i = 8;
	nb_cluster = size / TINY_CLUSTER_LEN;
	if (size % TINY_CLUSTER_LEN)
		nb_cluster++;
	while (++i < MAX_CLUSTERS)
		if (check_mapping(&i, header->mapping, nb_cluster))
		{
			new.addr = &header->start + (i * TINY_CLUSTER_LEN);
			break ;
		}
	new.size = size;
	new.next = NULL;
	new.free = 0;
	if (header->start)
		search_next_meta(header, header->start, new);
	else
		header->start = ft_memcpy(header->start_zone + sizeof(t_header),
				&new, sizeof(t_meta_data));
}

/*TODO 
 * remplir mapping de 1 apres la creation d'un nouveau meta_data modulo le nombre de cluster utilise
 * */

void	allocate_zone_tiny(t_header *tmp, size_t size)
{
	t_header	new;
	int			i;

	i = -1;
	tmp->next = mmap(NULL, TINY_ZONE, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	new.start = NULL;
	new.next = NULL;
	new.prev_addr = NULL;
	new.type = TINY;
	new.max_adjacent = 503 * 64;
	new.start_zone = tmp->next;
	tmp->next = ft_memcpy(tmp->next, &new, sizeof(t_header));
	while (++i < 9) // Condamnation des 9 premiers clusters pour la structure header
		tmp->mapping[i] = '1';
}

void	*malloc_tiny(size_t size)
{
	t_header	*tmp;
	tmp = &g_data; // assignation sur tmp pour ne pas perdre le pointeur de début de g_data
	while (tmp) // recherche d'une zone éligible
	{
		if (tmp->type == 0 && tmp->max_adjacent > size + sizeof(t_meta_data))
		{
//			addr = allocate_cluster(tmp, size, TINY_CLUSTER_LEN);
			return (tmp->start->addr);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	allocate_zone_tiny(tmp, size); // allocation d'une nouvelle zone si aucune valide
	return (tmp->start->addr);
}

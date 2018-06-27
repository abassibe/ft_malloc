/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 01:54:47 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:16 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>
#include "libft.h"

# define TINY					0 // ID
# define MAX_TINY				256 // taille demandée maximale pour une allocation de type tinnyi
# define TINY_ZONE				32768 // taille totale de la zone/map (100 allocations de type tinny
# define TINY_CLUSTER_LEN		64 // sous division de la zone/map (allocation minimale, toujours multiple de cette valeur ex: 70 octets demandé = 2 Cluster alloués)
# define SMALL					1 // ID
# define MAX_SMALL				512 // taille demandée maximale pour une allocation de type small
# define SMALL_ZONE				57344 // taille totale de la zone/map (100 allocations de type small
# define SMALL_CLUSTER_LEN		112 // sous division de la zone/map (allocation minimale, toujours multiple de cette valeur ex: 120 octets demandé = 2 Cluster alloués)
# define MAX_CLUSTERS			512 // cluster maximum pour chaque zone/map
//# define LARGE			2

/* structure de début de chaque zone/map */
typedef struct			s_meta_data
{
	void				*addr;
	size_t				size;
	struct s_meta_data	*next;
	int					free;
}						t_meta_data;

/* structure de début de zone/map */
typedef struct			s_header
{
	t_meta_data			*start;
	struct s_header		*next;
	void				*start_zone;
	char				mapping[MAX_CLUSTERS];
	void				*prev_addr;
	int					type;
	int					max_adjacent;
}						t_header;

extern t_header			g_data;

void					*ft_malloc(size_t size);
void					*malloc_tiny(size_t size);
void					show_alloc_mem();
void					show_alloc_mem_better_than_show_alloc_mem();
void					allocate_zone_tiny(t_header *tmp, size_t size);

#endif

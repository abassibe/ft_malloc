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

# define TINY					0
# define MAX_TINY				256
# define TINY_ZONE				32768
# define TINY_CLUSTER_LEN		64
# define SMALL					1
# define MAX_SMALL				512
# define SMALL_ZONE				57344
# define SMALL_CLUSTER_LEN		112
# define MAX_CLUSTERS			512
//# define LARGE			2

typedef struct			s_meta_data
{
	void				*addr;
	size_t				size;
	struct s_meta_data	*next;
	int					free;
}						t_meta_data;

typedef struct			s_header
{
	t_meta_data			*start;
	struct s_header		*next;
	void				*start_zone;
	char				mapping[512];
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

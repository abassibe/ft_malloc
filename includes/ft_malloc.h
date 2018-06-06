/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 01:54:47 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/06 02:51:56 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>

# define TINY			256
# define TINY_ZONE		32768
# define TINY_CLUSTER	64
# define SMALL			512
# define SMALL_ZONE		57344
# define SMALL_CLUSTER	128

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
	char				*mapping;
	int					flag;
}						t_header;

extern t_meta_data		g_data;

void					*ft_malloc(size_t size);

#endif

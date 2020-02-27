/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 01:54:47 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/27 04:31:52 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include "libft.h"

# define MIN_ALLOC_BY_ZONE 100
# define MAX_TINY_SIZE 128
# define MAX_SMALL_SIZE 1024

typedef enum		e_size_type
{
	TINY,
	SMALL,
	LARGE
}					t_page_type;

typedef struct		s_meta_data
{
	void				*addr;
	struct s_meta_data	*prev;
	struct s_meta_data	*next;
	size_t				size;
	int					free;
}					t_meta_data;

typedef struct		s_header
{
	struct s_header	*next_zone;
	t_meta_data		*first_elem;
	t_page_type		type;
}					t_header;

typedef struct		s_env_debug
{
	char	*debug_report;
	char	*guard_edges;
	char	*do_not_protect_prelude;
	char	*do_not_protect_postlude;
	char	*error_abort;
}					t_env_debug;

extern int			g_total_mmap_size_allocated;
extern int			g_total_allocation_request;
extern int			g_total_free_request;

pthread_mutex_t		g_mutex;

t_env_debug			g_debug;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);
void				show_alloc_mem(void);
void				malloc_dump(void);

t_header			*get_struct(void);
t_header			**first_alloc(void);
t_header			*init_header(size_t size);
t_header			*allocate_large(t_header *page, size_t size);

void				*create_allocation(t_header *data, size_t size,
		t_page_type type);
int					looking_for_place(t_meta_data *region, t_page_type type);
t_header			*new_zone(t_page_type type, size_t size);

void				free_large_zone(t_header *data, t_header *preview);
void				free_tiny_small_zone(t_header *data, t_header *preview,
		t_meta_data *tmp);

t_page_type			get_page_type(size_t size);
void				init_meta_data(t_header *data, size_t size,
		t_page_type type);
void				malloc_stats(void);
int					print_bloc_address(t_meta_data *tmp);

void				print_value(unsigned long val);
void				print_address(unsigned long val);
void				useless_layer(unsigned char val, char *color);

void				*print_error(char *error, int crash, void *ret);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 01:54:47 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 06:19:16 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "libft.h"

#define PAGE_SIZE getpagesize()																									 // Taille des pages allouées par le système
#define MIN_ALLOC_BY_ZONE 100																									 // Allocation maximum par zone
#define MAX_TINY_SIZE 128																										 // Taille maximale pour une allocation de type tinny
#define MAX_TINY_ZONE ((((((128 + sizeof(t_meta_data)) * MIN_ALLOC_BY_ZONE) + sizeof(t_header)) / PAGE_SIZE) + 1) * PAGE_SIZE)   // Taille maximale pour une zone de type tinny
#define MAX_SMALL_SIZE 1024																										 // Taille maximale pour une allocation de type small
#define MAX_SMALL_ZONE ((((((1024 + sizeof(t_meta_data)) * MIN_ALLOC_BY_ZONE) + sizeof(t_header)) / PAGE_SIZE) + 1) * PAGE_SIZE) // Taille maximale pour une zone de type small

/* Type d'allocation selon la taille demandée */
typedef enum e_size_type
{
	TINY,
	SMALL,
	LARGE
} t_page_type;

/* Structure de début de chaque allocation */
typedef struct s_meta_data //size 40
{
	void *addr;				  // Pointeur sur la région allouée et retournée (après header)
	struct s_meta_data *prev; // Allocation précédente
	struct s_meta_data *next; // Allocation suivante
	size_t size;			  // Taille de la région allouée (sans header)
	int free;				  // O si allouée et non free, sinon 1
} t_meta_data;

/* Structure de début de zone */
typedef struct s_header //size 24
{
	struct s_header *next_zone; // Pointeur sur zone suivante
	t_meta_data *first_elem;	// Pointeur sur première allocation de la zone courante
	t_page_type type;			// Définit quel type d'allocation cette zone gère
} t_header;

typedef struct s_env_debug
{
	char *malloc_debug_report;
	char *malloc_guard_edges;
	char *malloc_do_not_protect_prelude;
	char *malloc_do_not_protect_postlude;
	char *malloc_error_abort;
} t_env_debug;

extern unsigned long total_mmap_size_allocated;

extern unsigned long total_allocation_request;

extern unsigned long total_free_request;

pthread_mutex_t g_mutex;

t_env_debug g_debug;

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);
extern void show_alloc_mem(void);
extern void *calloc(size_t count, size_t size);

t_header *get_struct(void);
t_header **first_alloc(void);
t_header *init_header(size_t size);
t_header *allocate_large(t_header *page, size_t size);

void *create_allocation(t_header *data, size_t size, t_page_type type);
int looking_for_place(t_meta_data *region, t_page_type type);
t_header *new_zone(t_page_type type, size_t size);

void free_large_zone(t_header *data, t_header *preview, void *ptr);
void free_tiny_small_zone(t_header *data, t_header *preview, t_meta_data *tmp, void *ptr);

t_page_type get_page_type(size_t size);
void init_meta_data(t_header *data, size_t size);
void malloc_stats(void);

void malloc_dump(void);

void *print_error(char *error, int crash, void *ret);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 02:25:52 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/27 04:14:53 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int			g_total_mmap_size_allocated = 0;
int			g_total_allocation_request = 0;
int			g_total_free_request = 0;
t_env_debug	g_debug;

void		*print_error(char *error, int crash, void *ret)
{
	if (g_debug.error_abort)
	{
		write(2, error, ft_strlen(error));
		abort();
	}
	if (g_debug.debug_report &&
		!ft_strcmp(g_debug.debug_report, "crash") && crash)
		write(2, error, ft_strlen(error));
	else if (g_debug.debug_report &&
			!ft_strcmp(g_debug.debug_report, "none"))
		return (ret);
	else
		write(2, error, ft_strlen(error));
	return (ret);
}

static void	get_env_debug(void)
{
	g_debug.debug_report = getenv("MallocDebugReport");
	g_debug.guard_edges = getenv("MallocGuardEdges");
	g_debug.do_not_protect_prelude = getenv("MallocDoNotProtectPrelude");
	g_debug.do_not_protect_postlude = getenv("MallocDoNotProtectPostlude");
	g_debug.error_abort = getenv("MallocErrorAbort");
}

static void	*new_allocation(t_header *data, size_t size)
{
	t_header	*header;
	t_page_type	type;

	type = get_page_type(size);
	header = data;
	while (header)
	{
		if (header->type == type &&
				looking_for_place(header->first_elem, type) != -1)
			return (create_allocation(header, size, type));
		if (!header->next_zone)
			break ;
		header = header->next_zone;
	}
	header->next_zone = new_zone(type, size);
	return (header->next_zone->first_elem->addr);
}

void		*malloc(size_t size)
{
	t_header	*data;
	void		*ret;

	pthread_mutex_lock(&g_mutex);
	g_total_allocation_request++;
	get_env_debug();
	if (size <= 0)
		return (print_error("", 1, NULL));
	data = get_struct();
	if (!data)
		return (&*init_header(size)->first_elem->addr);
	if (!(ret = new_allocation(data, size)))
		return (print_error("", 1, NULL));
	pthread_mutex_unlock(&g_mutex);
	return (&*ret);
}
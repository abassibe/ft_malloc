/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:56:34 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/27 00:54:01 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*calloc(size_t count, size_t size)
{
	void *ret;

	pthread_mutex_lock(&g_mutex);
	ret = malloc(count * size);
	ft_memset(ret, '\0', (count * size));
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

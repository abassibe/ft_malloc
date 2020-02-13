/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 03:44:19 by abassibe          #+#    #+#             */
/*   Updated: 2018/06/08 03:39:53 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void printData(t_header *g_data, size_t size)
{
	t_header *tmp = g_data;
	int count = 0;
	int zoneCount = 0;

	while (g_data)
	{
		if (g_data->type == TINY)
		{
			printf("TINY ZONE = %lu\n", MAX_TINY_ZONE);
			for (int i = 0; i < MAX_TINY_ZONE && i + MAX_TINY_SIZE + sizeof(t_meta_data) < MAX_TINY_ZONE; i++)
			{
				if (i < sizeof(t_header))
				{
					if (i == 0)
						printf("\033[0;31m%p\n", (char *)g_data);
					printf("\033[0;31m[% 4d]", ((char *)g_data)[i]);
					if (i + 1 == sizeof(t_header))
						printf("\n");
					continue;
				}
				for (int j = i; j < MAX_TINY_ZONE && j < i + MAX_TINY_SIZE + sizeof(t_meta_data); j++)
				{
					if (i == j)
						printf("\033[0;31m%p\n", (char *)g_data + j);
					if (j < i + sizeof(t_meta_data))
						printf("\033[0;31m[% 4d]", ((char *)g_data)[j]);
					else
						printf("\033[0;32m[% 4d]", ((char *)g_data)[j]);
					if (j + 1 >= i + MAX_TINY_SIZE + sizeof(t_meta_data))
					{
						i = j;
						count++;
						printf("\ni = %d, région #%d, region size = %lu, zone #%d\n", i, count, MAX_SMALL_SIZE + sizeof(t_meta_data), zoneCount);
						break;
					}
				}
			}
		}
		else if (g_data->type == SMALL)
		{
			printf("SMALL ZONE = %lu\n", MAX_SMALL_ZONE);
			for (int i = 0; i < MAX_SMALL_ZONE; i++)
			{
				if (i < sizeof(t_header))
				{
					if (i == 0)
						printf("\033[0;31m%p\n", (char *)g_data);
					printf("\033[0;31m[% 4d]", ((char *)g_data)[i]);
					if (i + 1 == sizeof(t_header))
						printf("\n");
					continue;
				}
				for (int j = i; j < MAX_SMALL_ZONE && j < i + MAX_SMALL_SIZE + sizeof(t_meta_data); j++)
				{
					if (i == j)
						printf("\033[0;31m%p\n", (char *)g_data + j);
					if (j < i + sizeof(t_meta_data))
						printf("\033[0;31m[% 4d]", ((char *)g_data)[j]);
					else
						printf("\033[0;32m[% 4d]", ((char *)g_data)[j]);
					if (j + 1 >= i + MAX_SMALL_SIZE + sizeof(t_meta_data))
					{
						i = j;
						count++;
						printf("\ni = %d, région #%d, region size = %lu, zone #%d\n", i, count, MAX_SMALL_SIZE + sizeof(t_meta_data), zoneCount);
						break;
					}
				}
			}
		}
		else
		{
			printf("LARGE ZONE = %lu\n", size);
			for (int i = 0; i < size; i++)
			{
				if (i < sizeof(t_header))
				{
					printf("\033[0;31m[% 4d]", ((char *)g_data)[i]);
					if (i + 1 == sizeof(t_header))
						printf("\n");
					continue;
				}
				if (i == (sizeof(t_header) + sizeof(t_meta_data)))
					printf(" ");
				printf("\033[0;34m[% 4d]", ((char *)g_data)[i]);
			}
		}
		printf("\n");
		g_data = g_data->next_zone;
		zoneCount++;
	}
	printf("end of first zone");
}

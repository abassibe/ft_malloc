/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 05:54:59 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/29 05:56:18 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "../includes/malloc.h"

void *thread_1(void *arg)
{
	char *str;

	str = malloc(10);
	str = realloc(str, 20);
	printf("Thread 1\n");
	free(str);
	pthread_exit(NULL);
}

void *thread_2(void *arg)
{
	char *str;

	str = malloc(10);
	str = realloc(str, 20);
	printf("Thread 2\n");
	free(str);
	pthread_exit(NULL);
}

void *thread_3(void *arg)
{
	char *str;

	str = malloc(10);
	str = realloc(str, 20);
	printf("Thread 3\n");
	free(str);
	pthread_exit(NULL);
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	pthread_create(&thread1, NULL, thread_1, NULL);
	pthread_create(&thread2, NULL, thread_2, NULL);
	pthread_create(&thread3, NULL, thread_3, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	return (0);
}

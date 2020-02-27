/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 10:17:57 by abassibe          #+#    #+#             */
/*   Updated: 2020/02/27 01:13:53 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		print_value(unsigned long val)
{
	char	c[1];

	c[0] = 0;
	if (val > 0)
	{
		c[0] = val % 10 + '0';
		val = val / 10;
		print_value(val);
	}
	write(1, c, 1);
}

void		print_address(unsigned long val)
{
	char	c[1];
	char	*tab;

	tab = "0123456789abcdef";
	c[0] = 0;
	if (val > 0)
	{
		c[0] = tab[val % 16];
		val = val / 16;
		print_address(val);
	}
	else
		write(1, "\033[0;0m0x", 8);
	write(1, c, 1);
}

static void	print_hexa(unsigned char val)
{
	char	c[1];
	char	*tab;

	tab = "0123456789abcdef";
	c[0] = 0;
	if (val > 0)
	{
		c[0] = tab[val % 16];
		val = val / 16;
		print_hexa(val);
	}
	write(1, c, 1);
}

void		useless_layer(unsigned char val, char *color)
{
	write(1, color, ft_strlen(color));
	write(1, " ", 1);
	if (val < 16)
		write(1, "0", 1);
	if (val == 0)
		write(1, "0", 1);
	print_hexa(val);
}

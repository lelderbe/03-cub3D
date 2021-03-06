/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils_p2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:03:06 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/06 21:11:45 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

static int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

static int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

static int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int			add_shade(double d, unsigned color)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = get_t(color);
	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	return (create_trgb(t,
			(int)(r - r * d),
			(int)(g - g * d),
			(int)(b - b * d)));
}

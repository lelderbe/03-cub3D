/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:39:50 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/25 19:10:13 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}
/*
int		add_shade(double d, int color)
{
	return (create_trgb(
			get_t,
			(int)(get_r - get_r * d),
			(int)(get_g - get_g * d),
			(int)(get_b - get_b * d)
			));
}
*/
void	img_pixel_put(t_img *img, double x, double y, int color)
{
	int		xx;
	int		yy;
    char    *dst;

	xx = (int)(x);
	yy = (int)(y);
    dst = img->addr + (yy * img->len + xx * (img->bpp / 8));
    *(unsigned int*)dst = color;
}


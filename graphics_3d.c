/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:55:23 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 16:37:29 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_cub *e, int dx, int dy)
{
	unsigned	color;
	int			addr;
	t_img		wall;

	wall = e->w[e->side];
	color = e->wall_color;
	color = USE_MANY_COLORS ? e->color : color;
	addr = dy * wall.len + dx * (wall.bpp / 8);
	color = USE_TEXTURES ? *((unsigned int*)(wall.addr + addr)) : color;
	//color = USE_FOG ? (int)(255 / (1 + d * d * 0.1)) : color;
	return (color);
}

void		display_3d_floor_ceil(t_cub *e)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			color = y < e->height / 2 ? e->ceil_color : e->floor_color;
			img_pixel_put(&e->main, x, y, color);
			x++;
		}
		y++;
	}
}

void		display_3d_column(t_cub *e, int column, double d)
{
	int		i;
	int		height;
	double	step;
	int		dx;
	double	dy;

	height = (int)(e->dpp / d);
	e->hit = e->side == E_WALL || e->side == W_WALL ? e->hit_y : e->hit_x;
	dy = 0;
	step = 1.0 * e->w[e->side].height / height;
	if (height >= e->height)
	{
		dy = step * (height - e->height) / 2;
		height = e->height - 1;
	}
	dx = (int)(e->w[e->side].width * e->hit);
	i = -height / 2;
	while (i < height / 2)
	{
		img_pixel_put(&e->main, column, e->height / 2 + i,
										get_color(e, dx, floor(dy)));
		dy = dy + step;
		i++;
	}
}
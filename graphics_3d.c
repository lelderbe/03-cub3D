/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:55:23 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/05 15:26:54 by lelderbe         ###   ########.fr       */
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
			color = y < e->height / 2 ? e->c_clr : e->f_clr;
			img_pixel_put(&e->main, x, y, color);
			x++;
		}
		y++;
	}
}

void		display_3d_column_v2(t_cub *e, int column, double d)
{
	int		dx;
	double	dy;
	int		y;

	e->t_h = (int)(e->dpp / d);
	e->t_st = 1.0 * e->w[e->side].height / e->t_h;
	dy = e->t_h >= e->height ? e->t_st * (e->t_h - e->height) / 2 : 0;
	e->t_h = e->t_h >= e->height ? e->height : e->t_h;
	dx = (int)(e->w[e->side].width * e->hit);
	e->y_ceil = (e->height - e->t_h) >> 1;
	e->y_floor = e->height - e->y_ceil;
	y = 0;
	while (y < e->height)
	{
		if (y < e->y_ceil)
			img_pixel_put(&e->main, column, y, e->c_clr);
		if (y >= e->y_ceil && y <= e->y_floor)
		{
			img_pixel_put(&e->main, column, y, get_color(e, dx, floor(dy)));
			dy = dy + e->t_st < e->w[e->side].height ? dy + e->t_st : dy;
		}
		if (y > e->y_floor)
			img_pixel_put(&e->main, column, y, e->f_clr);
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

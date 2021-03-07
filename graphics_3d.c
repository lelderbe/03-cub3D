/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:55:23 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/07 11:43:13 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_cub *e, int dx, int dy)
{
	unsigned	color;
	int			addr;
	t_img		wall;

	wall = e->w[e->side];
	color = e->w_clr;
	color = USE_MANY_COLORS ? e->color : color;
	addr = dy * wall.len + dx * (wall.bpp / 8);
	color = USE_TEXTURES ? *((unsigned int*)(wall.addr + addr)) : color;
	return (color);
}

void		display_3d_column(t_cub *e, int column, double d)
{
	int		dx;
	double	dy;
	int		y;

	e->t_h = e->wall ? (int)(e->dpp / d) : 0;
	e->t_st = 1.0 * e->w[e->side].h / e->t_h;
	dy = e->t_h >= e->height ? e->t_st * (e->t_h - e->height) / 2 : 0;
	e->t_h = e->t_h >= e->height ? e->height : e->t_h;
	dx = (int)(e->w[e->side].w * e->hit);
	e->y_ceil = (e->height - e->t_h) >> 1;
	e->y_floor = e->height - e->y_ceil;
	y = 0;
	while (y < e->height)
	{
		if (y < e->y_ceil)
			img_pixel_put(&e->main, column, y, e->c_clr);
		if (y >= e->y_ceil && y < e->y_floor)
		{
			img_pixel_put(&e->main, column, y, get_color(e, dx, floor(dy)));
			dy = dy + e->t_st < e->w[e->side].h ? dy + e->t_st : dy;
		}
		if (y >= e->y_floor)
			img_pixel_put(&e->main, column, y, e->f_clr);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:14:50 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/05 15:10:25 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	check_vert_lines(t_cub *e, double cos_a, double sin_a)
{
	double d;
	double x;
	double y;
	double dx;
	double dy;

	x = cos_a >= 0 ? (int)(e->pl_x + 1) : (int)e->pl_x - 0.000001;
	d = (x - e->pl_x) / cos_a;
	y = e->pl_y + d * sin_a;
	dx = cos_a >= 0 ? 1 : -1;
	dy = (dx / cos_a) * sin_a;
	while (x >= 0 && x < e->map_width && y >= 0 && y < e->map_height &&
				e->map[(int)y][(int)x] != MAP_WALL)
	{
		e->vis[(int)y][(int)x] = '1';
		x += dx;
		y += dy;
	}
	e->side_v = dx > 0 ? E_WALL : W_WALL;
	e->hit_y = y - (int)(y);
	e->vcolor = (int)y * 30;
	d = (x - e->pl_x) / cos_a;
	return (fabs(d));
}

static double	check_horiz_lines(t_cub *e, double cos_a, double sin_a)
{
	double d;
	double x;
	double y;
	double dx;
	double dy;

	y = sin_a >= 0 ? (int)(e->pl_y + 1) : (int)e->pl_y - 0.000001;
	d = (y - e->pl_y) / sin_a;
	x = e->pl_x + d * cos_a;
	dy = sin_a >= 0 ? 1 : -1;
	dx = (dy / sin_a) * cos_a;
	while (x >= 0 && x < e->map_width && y >= 0 && y < e->map_height &&
				e->map[(int)y][(int)x] != MAP_WALL)
	{
		e->vis[(int)y][(int)x] = '1';
		x += dx;
		y += dy;
	}
	e->side_h = dy > 0 ? S_WALL : N_WALL;
	e->hit_x = x - (int)(x);
	e->hcolor = (int)x * 30;
	d = (y - e->pl_y) / sin_a;
	return (fabs(d));
}

static double	cast_ray(double ang, t_cub *e)
{
	double	d;
	double	dh;
	double	dv;

	dv = check_vert_lines(e, cos_a(ang), sin_a(ang));
	dh = check_horiz_lines(e, cos_a(ang), sin_a(ang));
	d = dh < dv ? dh : dv;
	e->side = dh < dv ? e->side_h : e->side_v;
	e->hit = dh < dv ? e->hit_x : e->hit_y;
	e->color = dh < dv ? e->hcolor : e->vcolor;
	return (d);
}

void			pl_move(t_cub *e, double dx, double dy)
{
	double x;
	double y;

	x = e->pl_x + dx;
	x = dx > 0 ? x + BODY / 2 : x - BODY / 2;
	y = e->pl_y;
	if (e->map[(int)y][(int)x] == MAP_WALL)
		x = dx > 0 ? (int)(x) - BODY / 2 : (int)(x + 1) + BODY / 2;
	else
		x = e->pl_x + dx;
	y = e->pl_y + dy;
	y = dy > 0 ? y + BODY / 2 : y - BODY / 2;
	if (e->map[(int)y][(int)x] == MAP_WALL)
		y = dy > 0 ? (int)(y) - BODY / 2 : (int)(y + 1) + BODY / 2;
	else
		y = e->pl_y + dy;
	e->pl_x = x;
	e->pl_y = y;
}

void			render(t_cub *e)
{
	double		d;
	double		ang;
	int			column;

	clear_2d_map_window(e);
	column = 0;
	while (column < e->width)
	{
		ang = e->atans[column];
		d = cast_ray(e->pl_a - ang, e);
		e->z[column] = d;
		display_2d_ray(e, e->pl_a - ang, d);
		d = d * cos_a(ang);
		display_3d_column_v2(e, column, d);
		column++;
	}
	draw_sprites(e);
	display_2d_map(e);
}

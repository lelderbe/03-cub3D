/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:14:50 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 18:30:57 by lelderbe         ###   ########.fr       */
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

//	printf("v= pl_x: %6.2f, pl_y: %6.2f, cos_a: %6.2f, sin_a: %6.2f\n", e->pl_x, e->pl_y, cos_a, sin_a);
	x = cos_a >= 0 ? (int)(e->pl_x + 1) : (int)e->pl_x - 0.000001;
	d = (x - e->pl_x) / cos_a;
	y = e->pl_y + d * sin_a;
//	printf("v= new x: %6.2f, new y: %6.2f, d: %6.2f\n", x, y, d);
	dx = cos_a >= 0 ? 1 : -1;
	dy = (dx / cos_a) * sin_a;
//	printf("v= d: %6.2f, dx: %6.2f, dy: %6.2f\n", d, dx, dy);
	while (x >= 0 && x < e->map_width && y >= 0 && y < e->map_height &&
				e->map[(int)y][(int)x] != MAP_WALL)
	{
		x += dx;
		y += dy;
//		printf("v= new x: %6.2f, new y: %6.2f\n", x, y);
	}
	e->side_v = dx > 0 ? E_WALL : W_WALL;
	e->hit_y = y - (int)(y);
	e->vcolor = (int)y * 30;
	//d = (x - e->pl_x) * cos(e->pl_a / 180 * M_PI) -
	//	(y - e->pl_y) * sin(e->pl_a / 180 * M_PI);
	//printf("v NEW d: %6.2f\n", d);
	//d = cos_a == 0 ? fabs(x - e->pl_x) : fabs(x - e->pl_x) / cos_a;
	d = (x - e->pl_x) / cos_a;
	//printf("v= ang: %6.2f, x: %d, y: %d, d: %6.3f\n", ang, (int)x, (int)y, d);
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
	//y = sin_a >= 0 ? (int)e->pl_y - 0.000001 : (int)(e->pl_y + 1);
	d = (y - e->pl_y) / sin_a;
	x = e->pl_x + d * cos_a;
	//dy = sin_a >= 0 ? -1 : 1;
	dy = sin_a >= 0 ? 1 : -1;
	dx = (dy / sin_a) * cos_a;
	while (x >= 0 && x < e->map_width && y >= 0 && y < e->map_height &&
				e->map[(int)y][(int)x] != MAP_WALL)
	{
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
	//printf("x: %6.2f, y: %6.2f\n", x, y);
	if (e->map[(int)y][(int)x] == MAP_WALL)
		x = dx > 0 ? (int)(x) - BODY / 2 : (int)(x + 1) + BODY / 2;
	else
		x = e->pl_x + dx;
	y = e->pl_y + dy;
	y = dy > 0 ? y + BODY / 2 : y - BODY / 2;
	//printf("x: %6.2f, y: %6.2f\n", x, y);
	if (e->map[(int)y][(int)x] == MAP_WALL)
		y = dy > 0 ? (int)(y) - BODY / 2 : (int)(y + 1) + BODY / 2;
	else
		y = e->pl_y + dy;
	//printf("final x: %6.2f, y: %6.2f\n", x, y);
	e->pl_x = x;
	e->pl_y = y;
}

void			render(t_cub *e)
{
	double	ang;
	double	fov_step;
	double	d;
	int		column;

	clear_2d_map_window(e);
	display_3d_floor_ceil(e);
	fov_step = 1.0 * FOV / e->width;
	ang = -HALF_FOV;
	//ang = 0;
	column = 0;
	while (column < e->width)
	{
		d = cast_ray(e->pl_a - ang, e);
		//ang = e->pl_a - HALF_FOV + fov_step * column;
		//d = cast_ray(ang, e);
		display_2d_ray(e, e->pl_a - ang, d);
		//display_2d_ray(e, ang, d);
		//printf("ang: %6.2f, old d: %6.3f\n", e->pl_a - i, d);
		//d = d * cos_a(ang);
		//printf("ang: %6.2f, corrected d: %6.3f\n", i, d);
		display_3d_column(e, column, d);
		ang += fov_step;
		column++;
	}
	display_2d_map(e);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:14:50 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/09 10:03:21 by lelderbe         ###   ########.fr       */
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
	e->wall_v = 0;
	while (abs((int)(x - e->pl_x)) < MAX_VIEW)
	{
		//if (y >= 0 && y < e->map_h && x >= 0 && x < ft_strlen(e->map[(int)y]) &&
		if (y >= 0 && y < e->map_h && x >= 0 && x < e->map_w &&
				e->map[(int)y][(int)x] == MAP_WALL)
		{
			e->wall_v = 1;
			break ;
		}
		x += dx;
		y += dy;
	}
	//e->wall_v = (y < 0 || y >= e->map_h || x < 0 || x >= e->map_w) ? 0 : 1;
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
	e->wall_h = 0;
	while (abs((int)(y - e->pl_y)) < MAX_VIEW)
	{
		//if (y >= 0 && y < e->map_h && x >= 0 && x < ft_strlen(e->map[(int)y]) &&
		if (y >= 0 && y < e->map_h && x >= 0 && x < e->map_w &&
				e->map[(int)y][(int)x] == MAP_WALL)
		{
			e->wall_h = 1;
			break ;
		}
		x += dx;
		y += dy;
	}
	//e->wall_h = (y < 0 || y >= e->map_h || x < 0 || x >= e->map_w) ? 0 : 1;
	e->side_h = dy > 0 ? S_WALL : N_WALL;
	e->hit_x = x - (int)(x);
	e->hcolor = (int)x * 30;
	d = (y - e->pl_y) / sin_a;
	return (fabs(d));
}

static double	cast_ray(t_cub *e, double ang)
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
	//e->wall = dh < dv ? e->wall_h : e->wall_v;
	e->wall = e->wall_h + e->wall_v;
	//e->wall = e->wall == 2 ? 1 : e->wall_v;
	return (d);
}

void			render(t_cub *e)
{
	double		d;
	double		ang;
	int			column;

	clear_2d_map_window(e);
	column = 0;
	while (column < e->main.w)
	{
		ang = e->atans[column];
		d = cast_ray(e, e->pl_a - ang);
		display_2d_ray(e, e->pl_a - ang, d);
		d = d * cos_a(ang);
		e->z[column] = d;
		display_3d_column(e, column, d);
		column++;
	}
	display_3d_sprites(e);
	display_2d_map(e);
}

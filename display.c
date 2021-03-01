/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/01 14:30:07 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_3d_floor_ceil(t_cub *e)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			// TODO: optimize (maybe via memcpy)
			color = y < e->height / 2 ? e->ceil_color : e->floor_color;
			img_pixel_put(&e->main, x, y, color);
			x++;
		}
		y++;
	}
}

double	check_vert_lines(t_cub *e, double cos_a, double sin_a)
{
	double d;
	double x;
	double y;
	double dx;
	double dy;

//	printf("v= pl_x: %6.2f, pl_y: %6.2f, cos_a: %6.2f, sin_a: %6.2f\n", e->pl_x, e->pl_y, cos_a, sin_a);
	x = (cos_a >= 0) ? (int)(e->pl_x + 1) : (int)e->pl_x - 0.000001;
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
	e->vhit = dx > 0 ? E_WALL : W_WALL;
	e->hit_y = y - (int)(y);
	e->vcolor = (int)y * 30;
	//d = (x - e->pl_x) * cos(e->pl_ang / 180 * M_PI) -
	//	(y - e->pl_y) * sin(e->pl_ang / 180 * M_PI);
	//printf("v NEW d: %6.2f\n", d);
	//d = cos_a == 0 ? fabs(x - e->pl_x) : fabs(x - e->pl_x) / cos_a;
	d = (x - e->pl_x) / cos_a;
	//printf("v= ang: %6.2f, x: %d, y: %d, d: %6.3f\n", ang, (int)x, (int)y, d);
	return (fabs(d));
}

double	check_horiz_lines(t_cub *e, double cos_a, double sin_a)
{
	double d;
	double x;
	double y;
	double dx;
	double dy;

//	printf("h= pl_x: %6.2f, pl_y: %6.2f, cos_a: %6.2f, sin_a: %6.2f\n", e->pl_x, e->pl_y, cos_a, sin_a);
	y = (sin_a >= 0) ? (int)(e->pl_y + 1) :	(int)e->pl_y - 0.000001;
	d = (y - e->pl_y) / sin_a;
	x = e->pl_x + d * cos_a;
//	printf("h= new x: %6.2f, new y: %6.2f, d: %6.2f\n", x, y, d);
	dy = sin_a >= 0 ? 1 : -1;
	dx = (dy / sin_a) * cos_a;
//	printf("h= d: %6.2f, dx: %6.2f, dy: %6.2f\n", d, dx, dy);
	while (x >= 0 && x < e->map_width && y >= 0 && y < e->map_height &&
				e->map[(int)y][(int)x] != MAP_WALL)
	{
		x += dx;
		y += dy;
//		printf("h= new x: %6.2f, new y: %6.2f\n", x, y);
	}
	e->hhit = dy > 0 ? S_WALL : N_WALL;
	e->hit_x = x - (int)(x);
	e->hcolor = (int)x * 30;
	//d = (x - e->pl_x) * cos(e->pl_ang / 180 * M_PI) -
	//	(y - e->pl_y) * sin(e->pl_ang / 180 * M_PI);
	//printf("h NEW d: %6.2f\n", d);
	//d = sin_a == 0 ? fabs(y - e->pl_y) : fabs(y - e->pl_y) / sin_a;
	d = (y - e->pl_y) / sin_a;
//	printf("h= ang: %6.2f, x: %d, y: %d, d: %6.3f\n", ang, (int)x, (int)y, d);
	return (fabs(d));
}

double		cast_ray(double ang, t_cub *e)
{
	double	d;
	double	dh;
	double	dv;

	e->ray_ang = ang;
	dv = check_vert_lines(e, cos_ang(ang), sin_ang(ang));
	dh = check_horiz_lines(e, cos_ang(ang), sin_ang(ang));
	e->side = dh < dv ? e->hhit : e->vhit;
	e->ray_d = dh < dv ? dh : dv;
	e->hit = dh < dv ? e->hhit : e->vhit;
	d = dh < dv ? dh : dv;
	e->color = dh < dv ? e->hcolor : e->vcolor;
	//printf("ang: %6.2f, new d: %6.3f, dx: %d, dy: %d\n", ang, d, dx, dy);
	return (d);
}

static int	get_color(t_cub *e, int dx, int dy)
{
	unsigned	color;
	int 		addr;
	t_tex		wall;

	wall = e->w[e->side];
	color = e->wall_color;
	color = USE_MANY_COLORS ? e->color : color;
	addr = dy * wall.len + dx * (wall.bpp / 8);
	color =	USE_TEXTURES ? *((unsigned int*)(wall.addr + addr)) : color;
	//color = USE_FOG ? (int)(255 / (1 + d * d * 0.1)) : color;
	return (color);
}

void		display_3d_column(t_cub *e, int x, double d)
{
	int		i;
	int		height;
	double	tex_step;
	int 	dx;
	double	dy;

	height = (int)(e->dpp / d);
	e->hit = e->side == E_WALL || e->side == W_WALL ? e->hit_y : e->hit_x;
	dy = 0;
	tex_step = 1.0 * e->w[e->side].height / height;
	if (height >= e->height)
	{
		dy = tex_step * (height - e->height) / 2;
		height = e->height - 1;
	}
	dx = (int)(e->w[e->side].width * e->hit);
	i = -height / 2;
	while (i < height / 2)
	{
		img_pixel_put(&e->main, x, e->height / 2 + i,
										get_color(e, dx, floor(dy)));
		dy = dy + tex_step;
		i++;
	}
}

void	render(t_cub *e)
{
	double	ang;
	double	fov_step;
	double	d;
	int		column;
	
	clear_2d_map_window(e);
	display_3d_floor_ceil(e);
	fov_step = 1.0 * FOV / e->width;
	ang = -HALF_FOV;
	column = 0;
	while (column < e->width)
	{
		d = cast_ray(e->pl_ang - ang, e);
		display_2d_ray(e);
		//printf("ang: %6.2f, old d: %6.3f\n", e->pl_ang - i, d);
		d = d * cos_ang(ang);
		//printf("ang: %6.2f, corrected d: %6.3f\n", i, d);
		display_3d_column(e, column, d);
		ang = ang + fov_step;
		column++;
	}
	display_2d_map(e);
}

void	world_update(t_cub *e)
{
	double dx;
	double dy;

	if (e->pl_a)
	{
		dx = cos((e->pl_ang + 90) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang + 90) / 180 * M_PI) * STEP;
		//log_pl(e);
		pl_check_and_move(e, dx, dy);
		//log_pl(e);
	}
	if (e->pl_w)
	{
		dx = cos((e->pl_ang - 0) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 0) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		//log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		//log_pl(e);
	}
	if (e->pl_s)
	{
		dx = cos((e->pl_ang - 180) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 180) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		//log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		//log_pl(e);
	}
	if (e->pl_d)
	{
		dx = cos((e->pl_ang - 90) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 90) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		//log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		//log_pl(e);
	}
	if (e->pl_left)
	{
		e->pl_ang += ANGLE_STEP;
		if (e->pl_ang >= 360)
			e->pl_ang -= 360;
		//log_pl(e);
	}
	if (e->pl_right)
	{
		e->pl_ang -= ANGLE_STEP;
		if (e->pl_ang < 0)
			e->pl_ang = 360 + e->pl_ang;
		//if (e->pl_ang <= -360)
		//	e->pl_ang += 360;
		//log_pl(e);
	}
}

int		repaint(t_cub *e)
{
	world_update(e);
	render(e);

	mlx_put_image_to_window(e->mlx, e->win, e->main.img, 0, 0);
	if (e->map_visible)
		mlx_put_image_to_window(e->mlx, e->win, e->mp.img, 0, 0);

	return (0);
}

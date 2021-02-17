/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/17 12:16:34 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static void	my_mlx_pixel_put(t_vars *e, int x, int y, int color)
static void	my_mlx_pixel_put(t_vars *e, double x, double y, int color)
{
	int	xx;
	int	yy;
    char    *dst;

	xx = round(x);
	yy = round(y);
    //dst = e->addr + (round(y * SCALE) * e->line_length +
	//	   round(x * SCALE) * (e->bits_per_pixel / 8));
    dst = e->addr + (yy * e->line_length + xx * (e->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static int	disp_ray(double ang, t_vars *e)
{
	//int x;
	//int y;
	double x;
	double y;
	double d;
	//int j;
	int xd;
	int yd;
	int xx;
	int yy;

	xd = 0;
	yd = 0;
	if (ang > 0 && ang < 180)
	{
		yd = -1;
	}
	else if (ang > 180 && ang < 360)
	{
		yd = 1;
	}
	if (ang > 90 && ang < 270)
	{
		xd = -1;
	}
	else if (ang < 90 || ang > 270)
	{
		xd = 1;
	}

	d = 0;
	while (d < MAX_VIEW)
	{
		//x = round(cos(ang / 180 * M_PI) * d);
		//y = -round(sin(ang / 180 * M_PI) * d);
		x = (cos(ang / 180 * M_PI) * d);
		y = -(sin(ang / 180 * M_PI) * d);
		//printf("ray x: %d y: %d\n", x / SCALE, y / SCALE);
		//if (e->map[(e->pl_y + y) / SCALE][(e->pl_x + x) / SCALE] == '1')
		//if (e->map[(round(e->pl_y + y))][round(e->pl_x + x)] == '1')
		xx = round(e->pl_x + x);
		yy = round(e->pl_y + y);
		if (e->map[yy][xx] == '1')
		{
			return ((int)d);
			break ;
		}
		//mlx_pixel_put(e->mlx, e->win, e->pl_x + x, e->pl_y + y, 0x0000FF00);
		my_mlx_pixel_put(e, e->pl_x * SCALE + x, e->pl_y * SCALE + y, 0x0000FF00);
		d = d + 1;
	}
	return (d);
}

void	disp_column(t_vars *e, int x, int d)
{
	int		i;
	int		h;

	(void)e;
	(void)d;
	h = round(1.0 * SCALE / d * e->d);
	printf("h: %d\n", h);
	i = -h / 2;
	while (i < h / 2)
	{
		//printf("x: %d, y: %d\n", x, e->height / 2 + i);
		//my_mlx_pixel_put(e, x, e->height / 2 + i, WALL_COLOR);
		my_mlx_pixel_put(e, x, e->height / 2 + i, WALL_COLOR);
		i++;
	}


}

void	disp_rays(t_vars *e)
{
	double	i;
	double	fov;
	double	fov_step;
	int		x;
	int		d;
	int		col;

	fov = FOV;
	x = e->width;
	fov_step = fov / e->width;

	i = -fov / 2;
	e->d = e->width / 2 / tan(fov / 2);
	col = 0;
	while (i <= fov / 2)
	{
		d = disp_ray(e->pl_ang - i, e);
		//printf("ang: %4.2f, d: %d\n", e->pl_ang - i, d);
		//disp_column(e, col, d);
		i = i + fov_step;
		col++;
	}
/*
	i = -fov / 2;
	e->d = e->width / 2 / tan(fov / 2);
	col = 0;
	while (i <= fov / 2)
	{
		d = disp_ray(e->pl_ang - i, e);
		//printf("ang: %4.2f, d: %d\n", e->pl_ang - i, d);
		i = i + fov_step;
		col++;
	}
	*/
}

static void	display_floor_ceil(t_vars *e)
{
	int x;
	int y;
	int color;

	(void)e;
	printf("floor and ceiling\n");
	printf("width: %d, height: %d\n", e->width, e->height);
	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			// TODO: optimize (maybe via memcpy)
			color = y < e->height / 2 ? CEIL_COLOR : FLOOR_COLOR;
			my_mlx_pixel_put(e, x, y, color);
			x++;
		}
		y++;
	}
}

void	disp_look_line(t_vars *e)
{
	int x;
	int y;
	int i;
	//int j;
	
	i = 0;
	while (i < LOOK_LEN)
	{
		x = round(cos(e->pl_ang / 180 * M_PI) * i);
		y = -round(sin(e->pl_ang / 180 * M_PI) * i);
		//printf("look x: %d y: %d\n", x, y);
		//mlx_pixel_put(e->mlx, e->win, e->pl_x + x, e->pl_y + y, 0x00FF0000);
		//my_mlx_pixel_put(e, e->pl_x + x, e->pl_y + y, 0x00FF0000);
		my_mlx_pixel_put(e, e->pl_x * SCALE + x,
				   e->pl_y * SCALE + y, 0x00FF0000);
		i++;
	}
}

void	display_wall_box(int x, int y, t_vars *e)
{
	int i;
	int j;
	int d;

	d = 1;
	j = 0 + d;
	while (j < SCALE - d)
	{
		i = 0 + d;
		while (i < SCALE - d)
		{
			//mlx_pixel_put(e->mlx, e->win, x * SCALE + i, y * SCALE + j, 0x00FFFFFF);
			my_mlx_pixel_put(e, x * SCALE + i, y * SCALE + j, 0x00FFFFFF);
			i++;
		}
		j++;
	}
}

void	display_pl(t_vars *e)
{
	int	i;
	int	j;
	//int x;
	//int y;
	double x;
	double y;

	i = 1;
	while (i < BODY / 2)
	{
		j = 0;
		while (j < 360)
		{
			//x = round(cos(1.0 * j / 180 * M_PI) * i);
			//y = -round(sin(1.0 * j / 180 * M_PI) * i);
			x = (cos(1.0 * j / 180 * M_PI) * i);
			y = -(sin(1.0 * j / 180 * M_PI) * i);
			//my_mlx_pixel_put(e, e->pl_x + x, e->pl_y + y, 0x0000FF00);
			my_mlx_pixel_put(e, e->pl_x * SCALE + x, e->pl_y * SCALE + y, 0x0000FF00);
			j++;
		}
		i++;
	}
	//disp_look_line(e);
}

void	display_map(t_vars *e)
{
	int	x;
	int	y;

	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if (e->map[y][x] == '1')
				display_wall_box(x, y, e);
			x++;
		}
		y++;
	}
}

void	repaint(t_vars *e)
{
	e->img = mlx_new_image(e->mlx, e->width, e->height);
    e->addr = mlx_get_data_addr(e->img, &e->bits_per_pixel, &e->line_length,
                                 &e->endian);
	printf("addr: %p\n", e->addr);
	printf("bits_per_pixel: %d\n", e->bits_per_pixel);
	printf("line_length: %d\n", e->line_length);
	printf("endian: %d\n", e->endian);

	display_floor_ceil(e);
	//disp_rays(e);
	display_map(e);
	display_pl(e);
	//disp_look_line(e);

    mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/23 15:27:42 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static void	my_mlx_pixel_put(t_vars *e, int x, int y, int color)
static void	my_mlx_pixel_put(t_vars *e, double x, double y, int color)
{
	int	xx;
	int	yy;
    char    *dst;

	xx = (int)(x);
	yy = (int)(y);
    //dst = e->addr + (round(y * SCALE) * e->line_length +
	//	   round(x * SCALE) * (e->bits_per_pixel / 8));
    dst = e->addr + (yy * e->line_length + xx * (e->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
/*
unsigned int	get_texture_pixel_color(t_vars *e, int x, int y)
{

}
*/
static double	disp_ray(double ang, t_vars *e)
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
		//printf("ang: %6.2f, ray x: %6.2f y: %6.2f\n", ang, x, y);
		//if (e->map[(e->pl_y + y) / SCALE][(e->pl_x + x) / SCALE] == '1')
		//if (e->map[(round(e->pl_y + y))][round(e->pl_x + x)] == '1')
		xx = (int)(e->pl_x + x);
		yy = (int)(e->pl_y + y);
		//printf("xx: %d, yy: %d\n", xx, yy);
		if (e->map[yy][xx] == '1')
		{
			e->wall_x = (e->pl_x + x) - (int)(e->pl_x + x);
			e->color = yy * 30 + xx * 30;
			//printf("wall\n");
			//d = d * cos(ang / 180 * M_PI);
			return (d);
			break ;
		}
		//mlx_pixel_put(e->mlx, e->win, e->pl_x + x, e->pl_y + y, 0x0000FF00);
		if (e->visible)
			my_mlx_pixel_put(e, (e->pl_x + x) * MAP_TILE, (e->pl_y + y) * MAP_TILE, 0x0000FF00);
		d = d + 1.0 / TILE;
	}
	//d = d * cos(ang / 180 * M_PI);
	return (d);
}

static double mod(double d)
{
	return (d < 0 ? -d : d);
}

//void	disp_column(t_vars *e, int x, int d)
void	disp_column(t_vars *e, int x, double d)
{
	int		i;
	int		h;
	unsigned int	color;
	double	step;
	double	shift;
	double		tex_y;
	int addr;
	int dx;
	int dy;
	t_wall wn;

	wn = e->w[1]; // NO

	shift = 0;
	tex_y = 0;
	//h = round(1.0 * SCALE / d * e->d);
	//printf("e->d: %6.2f, d: %6.2f\n", e->d, d);
	//h = (int)(1.0 * e->d * TILE / (d * TILE));
	//h = (int)(1.0 * e->d * TILE / d);
	h = (int)(e->d / d);
	//h = (round)(e->d / d);
	//printf("d: %6.2f, D: %6.2f, h: %d\n", e->d, d, h);
	step = 1.0 * wn.height / h;
	if (h >= e->height)
	{
		shift = step * (h - e->height) / 2;
		h = e->height - 1;
	}

	//step = 1.0 * e->n_height / h;
	dx = (int)wn.width * e->wall_x;
	//printf("h: %d, wall_x: %6.2f, column: %d\n", h, e->wall_x, column);

	i = -h / 2;
	while (i < h / 2)
	{
		//printf("x: %d, y: %d\n", x, e->height / 2 + i);
		//my_mlx_pixel_put(e, x, e->height / 2 + i, WALL_COLOR);
		//printf("color: %16.8f\n", (1 + d * d * 0.1));
		color = e->wall_color;
		color = (int)(255 / (1 + d * d * 0.1));
		color = e->color;
		
		//dy = shift + (int)tex_y;
		//dy = (int)(tex_y + shift);
		dy = floor(tex_y + shift);
		addr = dy * wn.len + dx * (wn.bpp / 8);
		color =	*((unsigned int*)(wn.addr + addr));
		//printf("dy: %d, addr: %d, color: %d\n", dy, addr, color);

		tex_y += step;
		my_mlx_pixel_put(e, x, e->height / 2 + i, color);
		i++;
	}
}

void	disp_rays(t_vars *e)
{
	double	i;
	double	fov;
	double	fov_step;
	double	d;
	int		col;

	fov = FOV;
	fov_step = 1.0 * FOV / e->width;

	mod(1);
	i = -HALF_FOV;
	//e->d = e->width / 2 / tan(fov / 2);
	col = 0;
	while (i <= HALF_FOV)
	{
		d = disp_ray(e->pl_ang - i, e);
		//printf("ang: %4.2f, d: %6.2f\n", e->pl_ang - i, d * TILE);
		//disp_column(e, col, d);
		//d = d * cos(mod(i) / 180 * M_PI);
		d = d * cos(i / 180 * M_PI);
		//printf("d: %6.2f\n", d);
		disp_column(e, col, d);
		i = i + fov_step;
		col++;
	}
}

static void	display_floor_ceil(t_vars *e)
{
	int x;
	int y;
	int color;

	//printf("width: %d, height: %d\n", e->width, e->height);
	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			// TODO: optimize (maybe via memcpy)
			color = y < e->height / 2 ? e->ceil_color : e->floor_color;
			my_mlx_pixel_put(e, x, y, color);
			x++;
		}
		y++;
	}
}

void	disp_look_line(t_vars *e)
{
	int dx;
	int dy;
	int i;
	//int j;
	int xx;
	int yy;
	
	if (!e->visible)
		return ;
	i = 0;
	//while (i < LOOK_LEN)
	while (i < (e->width * 2))
	{
		//x = round(cos(e->pl_ang / 180 * M_PI) * i);
		//y = -round(sin(e->pl_ang / 180 * M_PI) * i);
		dx = (cos(1.0 * e->pl_ang / 180 * M_PI) * i);
		dy = -(sin(1.0 * e->pl_ang / 180 * M_PI) * i);
		//printf("look x: %d y: %d\n", x, y);
		//mlx_pixel_put(e->mlx, e->win, e->pl_x + x, e->pl_y + y, 0x00FF0000);
		//my_mlx_pixel_put(e, e->pl_x + x, e->pl_y + y, 0x00FF0000);
		if ((int)(e->pl_x * MAP_TILE + dx) >= e->width ||
				(int)(e->pl_x * MAP_TILE + dx) < 0 ||
				(int)(e->pl_y * MAP_TILE + dy) >= e->height ||
				(int)(e->pl_y * MAP_TILE + dy) < 0)
			break ;
		
		
		xx = (int)(e->pl_x + 1.0 * dx / MAP_TILE);
		yy = (int)(e->pl_y + 1.0 * dy / MAP_TILE);
		//printf("xx: %d, yy: %d\n", xx, yy);
		if (e->map[yy][xx] == '1')
			break ;
		

		//printf("x: %6.2f, y: %6.2f\n", e->pl_x * MAP_TILE + x, e->pl_y * MAP_TILE + y);
		my_mlx_pixel_put(e, e->pl_x * MAP_TILE + dx, e->pl_y * MAP_TILE + dy, 0x00FF0000);
		//my_mlx_pixel_put(e, (e->pl_x + dx) * MAP_TILE, (e->pl_y + dy) * MAP_TILE, 0x00FF0000);
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
	while (j < MAP_TILE - d)
	{
		i = 0 + d;
		while (i < MAP_TILE - d)
		{
			//mlx_pixel_put(e->mlx, e->win, x * SCALE + i, y * SCALE + j, 0x00FFFFFF);
			my_mlx_pixel_put(e, x * MAP_TILE + i, y * MAP_TILE + j, 0x00FFFFFF);
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

	if (!e->visible)
		return ;
	i = 1;
	while (i < MAP_BODY / 2)
	{
		j = 0;
		while (j < 360)
		{
			//x = round(cos(1.0 * j / 180 * M_PI) * i);
			//y = -round(sin(1.0 * j / 180 * M_PI) * i);
			x = round(cos(1.0 * j / 180 * M_PI) * i);
			y = -round(sin(1.0 * j / 180 * M_PI) * i);
			//my_mlx_pixel_put(e, e->pl_x + x, e->pl_y + y, 0x0000FF00);
			my_mlx_pixel_put(e, e->pl_x * MAP_TILE + x, e->pl_y * MAP_TILE + y, 0x0000FF00);
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

	if (!e->visible)
		return ;
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

void	world_update(t_vars *e)
{
	double dx;
	double dy;

	if (e->pl_a)
	{
		dx = cos((e->pl_ang + 90) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang + 90) / 180 * M_PI) * STEP;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		log_pl(e);
	}
	if (e->pl_w)
	{
		dx = cos((e->pl_ang - 0) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 0) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		log_pl(e);
	}
	if (e->pl_s)
	{
		dx = cos((e->pl_ang - 180) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 180) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		log_pl(e);
	}
	if (e->pl_d)
	{
		dx = cos((e->pl_ang - 90) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 90) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		log_pl(e);
	}
	if (e->pl_left)
	{
		e->pl_ang += ANGLE_STEP;
		if (e->pl_ang >= 360)
			e->pl_ang -= 360;
		log_pl(e);
	}
	if (e->pl_right)
	{
		e->pl_ang -= ANGLE_STEP;
		if (e->pl_ang < 0)
			e->pl_ang = 360 + e->pl_ang;
		//if (e->pl_ang <= -360)
		//	e->pl_ang += 360;
		log_pl(e);
	}
}

void	texture_load(t_vars *e)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (e->w[i].file)
		{
			e->w[i].img = mlx_xpm_file_to_image(
					e->mlx, e->w[i].file, &e->w[i].width, &e->w[i].height);
			printf("tex width: %d, height: %d\n", e->w[i].width, e->w[i].height);
    		if (e->w[i].img)
			{
				e->w[i].addr = mlx_get_data_addr(
						e->w[i].img, &e->w[i].bpp, &e->w[i].len, &e->w[i].endian);
				log_img(e->w[i].addr, e->w[i].bpp, e->w[i].len, e->w[i].endian);
			}
		}
		/*
		if (e->wn.file)
		{
			e->wn.img = mlx_xpm_file_to_image(
					e->mlx, e->wn.file, &e->wn.width, &e->wn.height);
			printf("texture width: %d, height: %d\n", e->wn.width, e->wn.height);
    		if (e->wn.img)
			{
				e->wn.addr = mlx_get_data_addr(
						e->wn.img, &e->wn.bpp, &e->wn.len, &e->wn.endian);
				log_img(e->wn.addr, e->wn.bpp, e->wn.len, e->wn.endian);
			}
		}
		*/
		i++;
	}
}

int	repaint(t_vars *e)
{
	world_update(e);

	display_floor_ceil(e);
	disp_rays(e);
	display_map(e);
	display_pl(e);
	disp_look_line(e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);

	//mlx_destroy_image(e->mlx, e->img);
	return (0);
}

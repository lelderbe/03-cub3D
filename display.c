/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/26 15:05:19 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
unsigned int	get_texture_pixel_color(t_vars *e, int x, int y)
{

}
*/

static double mod(double d)
{
	return (d < 0 ? -d : d);
}

static double	disp_ray(double ang, t_vars *e)
{
	double x;
	double y;
	double d;
	int xd;
	int yd;
	
	return (0);
	xd = 0;
	yd = 0;
	if (ang > 0 && ang < 180)
		yd = -1;
	else if (ang > 180 && ang < 360)
		yd = 1;
	if (ang > 90 && ang < 270)
		xd = -1;
	else if (ang < 90 || ang > 270)
		xd = 1;

	d = 0;
	while (d < MAX_VIEW)
	{
		x = (cos(ang / 180 * M_PI) * d);
		y = -(sin(ang / 180 * M_PI) * d);
		//printf("ang: %6.2f, ray x: %6.2f y: %6.2f\n", ang, x, y);
		if (e->map[(int)(e->pl_y + y)][(int)(e->pl_x + x)] == '1')
		{
			e->wall_x = (e->pl_x + x) - (int)(e->pl_x + x);
			e->hit_x = (e->pl_x + x) - (int)(e->pl_x + x);
			e->hit_y = (e->pl_y + y) - (int)(e->pl_y + y);
			e->color = (int)(e->pl_y + y) * 30 + (int)(e->pl_x + x) * 30;
			//printf("ang: %6.2f, ray x: %6.3f y: %6.3f, d: %6.3f\n", ang, x, y, d);
			break ;
		}
		if (e->map_visible)
			if ((e->pl_x + x) * MAP_TILE < e->width && (e->pl_y + y) * MAP_TILE < e->height)
				img_pixel_put(&e->mp, (e->pl_x + x) * MAP_TILE, (e->pl_y + y) * MAP_TILE, 0x0000FF00);
		d = d + 1.0 / TILE;
	}
	//d = d * sin(ang / 180 * M_PI);
	//d = d * cos(i / 180 * M_PI);
	//printf("ang: %6.2f, ray x: %6.3f y: %6.3f, d: %6.3f\n", ang, x, y, d);
	return (d);
}

double	check_vert_lines(double ang, t_vars *e, double dx, double dy)
{
	double d;
	double x;
	double y;
	double cos_a;
	double sin_a;

	cos_a = cos(ang / 180 * M_PI);
	sin_a = -sin(ang / 180 * M_PI);
//	printf("v= pl_x: %6.2f, pl_y: %6.2f, cos_a: %6.2f, sin_a: %6.2f\n", e->pl_x, e->pl_y, cos_a, sin_a);
	if (cos_a >= 0)
		x = (int)(e->pl_x + 1);// + 0.01;
	else
		x = (int)e->pl_x - 0.01;

	//ay = e->pl_y + (e->pl_x - ax) * tan(ang / 180 * M_PI);
	d = (x - e->pl_x) / cos_a;
	y = e->pl_y + d * sin_a;
	y = y < 0 ? 0 : y;
//	printf("v= new x: %6.2f, new y: %6.2f, d: %6.2f\n", x, y, d);

	if (mod(d) > 1000)
		return (mod(d));
	//dy = -(dx) * tan(ang / 180 * M_PI);
	dx = cos_a >= 0 ? 1 : -1;
	e->vhit = dx > 0 ? 0 : 2;
	d = cos_a == 0 ? 1 : dx / cos_a;
	dy = d * sin_a;
//	printf("v= d: %6.2f, dx: %6.2f, dy: %6.2f\n", d, dx, dy);

	if (x >= e->map_max || y >= e->map_lines || x < 0 || y < 0)
		return (mod(d));

	while (e->map[(int)y][(int)x] != '1')
	{
		x += dx;
		y += dy;
//		printf("v= new x: %6.2f, new y: %6.2f\n", x, y);
		y = y < 0 ? 0 : y;
		if (x >= e->map_max || y >= e->map_lines || x < 0 || y < 0)
			break ;
	}

	//e->wall_x = (x) - (int)(x);
	//e->hit_x = (x) - (int)(x);
	e->hit_y = (y) - (int)(y);
	//e->color = (int)(y) * 30 + (int)(x) * 30;

	d = cos_a == 0 ? mod(x - e->pl_x) : mod(x - e->pl_x) / cos_a;
	//printf("v= ang: %6.2f, x: %d, y: %d, d: %6.3f\n", ang, (int)x, (int)y, d);
	printf("v= ang: %6.2f, x: %6.2f, y: %6.2f, d: %6.3f\n", ang, x, y, d);
	return (mod(d));
}

double	check_horiz_lines(double ang, t_vars *e, double dx, double dy)
{
	double d;
	double x;
	double y;
	double cos_a;
	double sin_a;

	cos_a = cos(ang / 180 * M_PI);
	sin_a = -sin(ang / 180 * M_PI);
//	printf("h= pl_x: %6.2f, pl_y: %6.2f, cos_a: %6.2f, sin_a: %6.2f\n", e->pl_x, e->pl_y, cos_a, sin_a);
	if (sin_a >= 0)
		y = (int)(e->pl_y + 1);// + 0.01;
	else
		y = (int)e->pl_y - 0.001;

	d = (y - e->pl_y) / sin_a;
	x = e->pl_x + d * cos_a;
	x = x < 0 ? 0 : x;
//	printf("h= new x: %6.2f, new y: %6.2f, d: %6.2f\n", x, y, d);

	if (mod(d) > 1000)
		return (mod(d));
	//dy = -(dx) * tan(ang / 180 * M_PI);
	dy = sin_a >= 0 ? 1 : -1;
	e->hhit = dy > 0 ? 3 : 1;
	d = sin_a == 0 ? 1 : dy / sin_a;
	dx = d * cos_a;
//	printf("h= d: %6.2f, dx: %6.2f, dy: %6.2f\n", d, dx, dy);

	if (x >= e->map_max || y >= e->map_lines || x < 0 || y < 0)
		return (mod(d));

	while (e->map[(int)y][(int)x] != '1')
	{
		x += dx;
		y += dy;
//		printf("h= new x: %6.2f, new y: %6.2f\n", x, y);
		//x = x < 0 ? 0 : x;
		//y = y < 0 ? 0 : y;
		if (x >= e->map_max || y >= e->map_lines || x < 0 || y < 0)
			break ;
	}

	//e->wall_x = (x) - (int)(x);
	e->hit_x = (x) - (int)(x);
	//e->hit_y = (y) - (int)(y);
	//e->color = (int)(y) * 30 + (int)(x) * 30;

	d = sin_a == 0 ? mod(y - e->pl_y) : mod(y - e->pl_y) / sin_a;
//	printf("h= ang: %6.2f, x: %d, y: %d, d: %6.3f\n", ang, (int)x, (int)y, d);
	printf("h= ang: %6.2f, x: %d, y: %d, d: %6.3f\n", ang, (int)x, (int)y, d);
	return (mod(d));
	/*
	ax = e->pl_x + (e->pl_y - ay) / tan(ang / 180 * M_PI);
	printf("h= ax: %6.2f, ay: %6.2f\n", ax, ay);

	dx = mod(dy) / tan(ang / 180 * M_PI);

	while (e->map[(int)ay][(int)ax] != '1')
	{
		ay += dy;
		ax += dx;
		printf("h= ax: %6.2f, ay: %6.2f\n", ax, ay);
	}

	d = (ax - e->pl_x) / cos(ang / 180 * M_PI);
	printf("h= ang: %6.2f, x: %d, y: %d, d: %6.3f\n", ang, (int)ax, (int)ay, d);
	return (d);
	*/
}

double	cast_ray(double ang, t_vars *e)
{
	//double x;
	//double y;
	double d;
	double dh;
	int dx;
	int dy;

	dx = 0;
	dy = 0;
	if (ang > 0 && ang < 180)
		dy = -1;
	else if (ang > 180 && ang < 360)
		dy = 1;
	if (ang > 90 && ang < 270)
		dx = -1;
	else if (ang < 90 || ang > 270)
		dx = 1;

	d = 0;
	//if (dy != 0)
	//	d = check_horiz_lines(ang, e, 0, dy);
	//if (dx != 0)
		d = check_vert_lines(ang, e, 0, 0);
		dh = check_horiz_lines(ang, e, 0, 0);
		e->hit = d < dh ? e->vhit : e->hhit;
		d = d < dh ? d : dh;
		//d = check_vert_lines(90, e, 0, 0);
	//printf("ang: %6.2f, new d: %6.3f, dx: %d, dy: %d\n", ang, d, dx, dy);
	return d;
/*
	d = 0;
	while (d < MAX_VIEW)
	{
		mx = (int)();
		x = (cos(ang / 180 * M_PI) * d);
		y = -(sin(ang / 180 * M_PI) * d);
		//printf("ang: %6.2f, ray x: %6.2f y: %6.2f\n", ang, x, y);
		if (e->map[(int)(e->pl_y + y)][(int)(e->pl_x + x)] == '1')
		{
			e->wall_x = (e->pl_x + x) - (int)(e->pl_x + x);
			e->hit_x = (e->pl_x + x) - (int)(e->pl_x + x);
			e->hit_y = (e->pl_y + y) - (int)(e->pl_y + y);
			e->color = (int)(e->pl_y + y) * 30 + (int)(e->pl_x + x) * 30;
			//printf("ang: %6.2f, ray x: %6.3f y: %6.3f, d: %6.3f\n", ang, x, y, d);
			break ;
		}
		if (e->map_visible)
			if ((e->pl_x + x) * MAP_TILE < e->width && (e->pl_y + y) * MAP_TILE < e->height)
				img_pixel_put(&e->mp, (e->pl_x + x) * MAP_TILE, (e->pl_y + y) * MAP_TILE, 0x0000FF00);
		d = d + 1.0 / TILE;
	}
	//d = d * sin(ang / 180 * M_PI);
	//d = d * cos(i / 180 * M_PI);
	//printf("ang: %6.2f, ray x: %6.3f y: %6.3f, d: %6.3f\n", ang, x, y, d);
	return (d);
*/
}

void	display_3d_column(t_vars *e, int x, double d)
{
	int				i;
	int				h;
	unsigned int	color;
	double			step;
	double			shift;
	double			tex_y;
	int 			addr;
	int 			dx;
	int 			dy;
	t_tex			wn;

	//wn = e->w[1]; // NO
	wn = e->w[e->hit]; // NO
	//wn = e->sprite; // NO

	e->wall_x = e->hit == 0 || e->hit == 2 ? e->hit_y : e->hit_x;
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
		//color = e->color;
		
		//dy = shift + (int)tex_y;
		//dy = (int)(tex_y + shift);
		dy = floor(tex_y + shift);
		addr = dy * wn.len + dx * (wn.bpp / 8);
		color =	*((unsigned int*)(wn.addr + addr));
		//printf("dy: %d, addr: %d, color: %d\n", dy, addr, color);

		tex_y += step;
		img_pixel_put(&e->main, x, e->height / 2 + i, color);
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
	//i = HALF_FOV - 1;
	//e->d = e->width / 2 / tan(fov / 2);
	col = 0;
	while (i <= HALF_FOV)
	{
		d = cast_ray(e->pl_ang - i, e);
		disp_ray(e->pl_ang - i, e);
		//printf("ang: %6.2f, old d: %6.3f\n", e->pl_ang - i, d);
		//printf("ang: %4.2f, d: %6.2f\n", e->pl_ang - i, d * TILE);
		//d = d * cos(mod(i) / 180 * M_PI);
		d = d * cos(i / 180 * M_PI);
		//printf("ang: %6.2f, d: %6.3f\n", i, d);
		//printf("d: %6.2f\n", d);
		display_3d_column(e, col, d);
		i = i + fov_step;
		col++;
	}
		//cast_ray(60, e);
}

static void	display_3d_floor_ceil(t_vars *e)
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
			//my_mlx_pixel_put(e, x, y, color);
			img_pixel_put(&e->main, x, y, color);
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
			//printf("tex width: %d, height: %d\n", e->w[i].width, e->w[i].height);
			if (e->w[i].img)
			{
				e->w[i].addr = mlx_get_data_addr(
						e->w[i].img, &e->w[i].bpp, &e->w[i].len, &e->w[i].endian);
				//log_img(e->w[i].addr, e->w[i].bpp, e->w[i].len, e->w[i].endian);
			}
		}
		i++;
	}
	e->sprite.img = mlx_xpm_file_to_image(
				e->mlx, e->sprite.file, &e->sprite.width, &e->sprite.height);
	//printf("tex width: %d, height: %d\n", e->sprite.width, e->sprite.height);
	if (e->sprite.img)
	{
		e->sprite.addr = mlx_get_data_addr(
				e->sprite.img, &e->sprite.bpp, &e->sprite.len, &e->sprite.endian);
		//log_img(e->sprite.addr, e->sprite.bpp, e->sprite.len, e->sprite.endian);
	}
}

int		repaint(t_vars *e)
{
	world_update(e);
	clear_2d_map_window(e);
	display_3d_floor_ceil(e);
	disp_rays(e);
	display_2d_map(e);

	mlx_put_image_to_window(e->mlx, e->win, e->main.img, 0, 0);
	if (e->map_visible)
		mlx_put_image_to_window(e->mlx, e->win, e->mp.img, 0, 0);

	return (0);
}

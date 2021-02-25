/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:13:18 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/25 19:21:48 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_2d_map_window(t_vars *e)
{
	int y;
	int x;

	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			// TODO: optimize
			img_pixel_put(&e->mp, x, y, 0xFF000000);
			x++;
		}
		y++;
	}

}

static void	display_2d_look_line(t_vars *e)
{
	int dx;
	int dy;
	int i;
	//int j;
	int xx;
	int yy;

	if (!e->map_visible)
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
		img_pixel_put(&e->mp, e->pl_x * MAP_TILE + dx, e->pl_y * MAP_TILE + dy, 0x00FF0000);
		//my_mlx_pixel_put(e, e->pl_x * MAP_TILE + dx, e->pl_y * MAP_TILE + dy, 0x00FF0000);
		//my_mlx_pixel_put(e, (e->pl_x + dx) * MAP_TILE, (e->pl_y + dy) * MAP_TILE, 0x00FF0000);
		i++;
	}
}

static void	display_2d_pl(t_vars *e)
{
	int	i;
	int	j;
	//int x;
	//int y;
	double x;
	double y;

	if (!e->map_visible)
		return ;
	i = 1;
	while (i < MAP_BODY / 2)
	{
		j = 0;
		while (j < 360)
		{
			x = round(cos(1.0 * j / 180 * M_PI) * i);
			y = -round(sin(1.0 * j / 180 * M_PI) * i);
			if (e->pl_x * MAP_TILE + x < e->width && e->pl_y * MAP_TILE + y < e->height)
				img_pixel_put(&e->mp, e->pl_x * MAP_TILE + x, e->pl_y * MAP_TILE + y, 0x0000FF00);
			j++;
		}
		i++;
	}
	display_2d_look_line(e);
}

static void	display_2d_wall_box(int x, int y, t_vars *e)
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
			if (x * MAP_TILE + i < e->width && y * MAP_TILE + j < e->height)
				img_pixel_put(&e->mp, x * MAP_TILE + i, y * MAP_TILE + j, 0x00FFFFFF);
			i++;
		}
		j++;
	}
}

void	display_2d_map(t_vars *e)
{
	int	x;
	int	y;

	if (!e->map_visible)
		return ;
	//clear_2d_map_window(e);
	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if (e->map[y][x] == '1')
				display_2d_wall_box(x, y, e);
			x++;
		}
		y++;
	}
	display_2d_pl(e);
}

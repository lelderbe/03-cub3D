/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:36:35 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/27 17:57:02 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_2d_look_line(t_vars *e)
{
	int		d;
	double	x;
	double	y;
	double	cos_a;
	double	sin_a;

	if (!e->map_visible)
		return ;
	cos_a = cos_ang(e->pl_ang);
	sin_a = sin_ang(e->pl_ang);
	d = 0;
	while (d < (e->width * 2))
	{
		x = (e->pl_x * MAP_TILE + cos_a * d);
		y = (e->pl_y * MAP_TILE + sin_a * d);
		if (x >= e->width || y >= e->height || x < 0 || y < 0)
			break ;
		if (e->map[(int)(y / MAP_TILE)][(int)(x / MAP_TILE)] == MAP_WALL)
			break ;
		img_pixel_put(&e->mp, x, y, 0x00FF0000);
		d++;
	}
}

static void	display_2d_pl(t_vars *e)
{
	int		i;
	int		angle;
	double	dx;
	double	dy;

	if (!e->map_visible)
		return ;
	i = 1;
	while (i < MAP_PL_BODY / 2)
	{
		angle = 0;
		while (angle < 360)
		{
			dx = round(cos_ang(angle) * i);
			dy = -round(sin_ang(angle) * i);
			if (e->pl_x * MAP_TILE + dx < e->width &&
					e->pl_y * MAP_TILE + dy < e->height)
				img_pixel_put(&e->mp, e->pl_x * MAP_TILE + dx,
								e->pl_y * MAP_TILE + dy, MAP_PL_BODY_COLOR);
			angle++;
		}
		i++;
	}
	display_2d_look_line(e);
}

static void	display_2d_wall_box(int x, int y, t_vars *e)
{
	int i;
	int j;
	int border;

	border = 1;
	j = 0 + border;
	while (j < MAP_TILE - border)
	{
		i = 0 + border;
		while (i < MAP_TILE - border)
		{
			if (x * MAP_TILE + i < e->width && y * MAP_TILE + j < e->height)
				img_pixel_put(&e->mp,
						x * MAP_TILE + i, y * MAP_TILE + j, MAP_COLOR);
			i++;
		}
		j++;
	}
}

void		display_2d_map(t_vars *e)
{
	int	x;
	int	y;

	if (!e->map_visible)
		return ;
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

void		display_2d_ray(t_vars *e)
{
	double	d;
	double	x;
	double	y;
	double	cos_a;
	double	sin_a;

	if (!e->map_visible || !MAP_RAYS_SHOW)
		return ;
	cos_a = cos_ang(e->ray_ang);
	sin_a = sin_ang(e->ray_ang);
	d = 0;
	while (d <= e->ray_d)
	{
		x = (e->pl_x + cos_a * d) * MAP_TILE;
		y = (e->pl_y + sin_a * d) * MAP_TILE;
		if ((int)x < e->width && (int)y < e->height)
			img_pixel_put(&e->mp, x, y, MAP_RAY_COLOR);
		d = d + MAP_RAY_STEP;
	}
}

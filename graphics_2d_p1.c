/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2d_p1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:36:35 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/09 11:26:38 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_2d_look_line(t_cub *e)
{
	int		d;
	double	x;
	double	y;
	double	cosa;
	double	sina;

	if (!e->map_visible)
		return ;
	cosa = cos_a(e->pl_a);
	sina = sin_a(e->pl_a);
	d = 0;
	while (d < (e->width * 2))
	{
		x = (e->pl_x * MAP_TILE + cosa * d);
		y = (e->pl_y * MAP_TILE + sina * d);
		if (x >= e->width || y >= e->height || x < 0 || y < 0)
			break ;
		if ((int)(y / MAP_TILE) < (int)e->map_h &&
			(int)(x / MAP_TILE) < (int)e->map_w &&
				e->map[(int)(y / MAP_TILE)][(int)(x / MAP_TILE)] == MAP_WALL)
			break ;
		img_pixel_put(&e->mp, x, y, 0x00FF0000);
		d++;
	}
}

static void	display_2d_pl(t_cub *e)
{
	int		i;
	int		angle;
	int		x;
	int		y;

	if (!e->map_visible)
		return ;
	i = 1;
	while (i < MAP_PL_BODY / 2)
	{
		angle = 0;
		while (angle < 360)
		{
			x = (int)(e->pl_x * MAP_TILE + round(cos_a(angle) * i));
			y = (int)(e->pl_y * MAP_TILE - round(sin_a(angle) * i));
			if (x >= 0 && x < e->width && y >= 0 && y < e->height)
				img_pixel_put(&e->mp, x, y, MAP_PL_BODY_COLOR);
			angle++;
		}
		i++;
	}
	display_2d_look_line(e);
}

static void	display_2d_wall_box(int x, int y, t_cub *e)
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

void		display_2d_ray(t_cub *e, double ray_ang, double ray_d)
{
	double	d;
	double	x;
	double	y;
	double	cosa;
	double	sina;

	if (!e->map_visible || !MAP_RAYS_SHOW || fabs(ray_ang - e->pl_a) > FOV / 2)
		return ;
	cosa = cos_a(ray_ang);
	sina = sin_a(ray_ang);
	d = 0;
	while (d <= ray_d)
	{
		x = (e->pl_x + cosa * d) * MAP_TILE;
		y = (e->pl_y + sina * d) * MAP_TILE;
		if ((int)x >= 0 && (int)x < e->width &&
			(int)y >= 0 && (int)y < e->height)
			img_pixel_put(&e->mp, x, y, MAP_RAY_COLOR);
		d = d + MAP_RAY_STEP;
	}
}

void		display_2d_map(t_cub *e)
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
			if (e->map[y][x] == '2')
				display_2d_sprites(x, y, e);
			x++;
		}
		y++;
	}
	display_2d_pl(e);
}

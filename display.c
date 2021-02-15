/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/05 15:16:27 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	disp_ray(double ang, t_vars *e)
{
	int x;
	int y;
	double i;
	//int j;
	int xd;
	int yd;

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

	i = 0;
	while (i < 1000)
	{
		x = round(cos(ang / 180 * M_PI) * i);
		y = -round(sin(ang / 180 * M_PI) * i);
		//printf("ray x: %d y: %d\n", x / SCALE, y / SCALE);
		if (e->map[(e->pl_y + y) / SCALE][(e->pl_x + x) / SCALE] == '1')
		{
			break ;
		}
		mlx_pixel_put(e->mlx, e->win, e->pl_x + x, e->pl_y + y, 0x0000FF00);
		i = i + 1;
	}
}

void	disp_rays(t_vars *e)
{
	double i;

	i = -10;
	while (i <= 10)
	{
		disp_ray(e->pl_ang + i, e);
		i = i + 0.5;
	}
}

void	repaint(t_vars *e)
{
	display_map(e);
	disp_rays(e);
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
		mlx_pixel_put(e->mlx, e->win, e->pl_x + x, e->pl_y + y, 0x00FF0000);
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
			mlx_pixel_put(e->mlx, e->win, x * SCALE + i, y * SCALE + j, 0x00FFFFFF);
			i++;
		}
		j++;
	}
}

void	display_pl(t_vars *e)
{
	int	i;
	int	j;

	j = - BODY / 2;
	while (j < BODY / 2)
	{
		i = - BODY / 2;
		while (i < BODY / 2)
		{
			mlx_pixel_put(e->mlx, e->win, e->pl_x + i, e->pl_y + j, 0x0000FF00);
			i++;
		}
		j++;
	}
	disp_look_line(e);
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
	display_pl(e);
}

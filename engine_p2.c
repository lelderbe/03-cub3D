/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/07 10:06:43 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pl_move(t_cub *e, double dx, double dy)
{
	double x;
	double y;

	x = e->pl_x + dx;
	x = dx > 0 ? x + BODY / 2 : x - BODY / 2;
	y = e->pl_y;
	if (WALL_COLLISION && e->map[(int)y][(int)x] == MAP_WALL)
		x = dx > 0 ? (int)(x) - BODY / 2 : (int)(x + 1) + BODY / 2;
	else
		x = e->pl_x + dx;
	y = e->pl_y + dy;
	y = dy > 0 ? y + BODY / 2 : y - BODY / 2;
	if (WALL_COLLISION && e->map[(int)y][(int)x] == MAP_WALL)
		y = dy > 0 ? (int)(y) - BODY / 2 : (int)(y + 1) + BODY / 2;
	else
		y = e->pl_y + dy;
	e->pl_x = x;
	e->pl_y = y;
}

static void	update_world(t_cub *e)
{
	if (e->pl_key_a)
		pl_move(e, cos_a(e->pl_a + 90) * STEP, sin_a(e->pl_a + 90) * STEP);
	if (e->pl_key_w)
		pl_move(e, cos_a(e->pl_a - 0) * STEP, sin_a(e->pl_a - 0) * STEP);
	if (e->pl_key_s)
		pl_move(e, cos_a(e->pl_a + 180) * STEP, sin_a(e->pl_a + 180) * STEP);
	if (e->pl_key_d)
		pl_move(e, cos_a(e->pl_a - 90) * STEP, sin_a(e->pl_a - 90) * STEP);
	if (e->pl_key_left)
	{
		e->pl_a += ANGLE_STEP;
		if (e->pl_a >= 360)
			e->pl_a += -360;
	}
	if (e->pl_key_right)
	{
		e->pl_a -= ANGLE_STEP;
		if (e->pl_a < -360)
			e->pl_a += 360;
	}
}

int			repaint(t_cub *e)
{
	update_world(e);
	render(e);
	mlx_put_image_to_window(e->mlx, e->win, e->main.img, -e->of, 0);
	if (e->map_visible)
		mlx_put_image_to_window(e->mlx, e->win, e->mp.img, 0, 0);
	return (0);
}

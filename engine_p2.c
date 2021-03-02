/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 17:34:42 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_world(t_cub *e)
{
	//log_pl(e);
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
			e->pl_a -= 360;
	}
	if (e->pl_key_right)
	{
		e->pl_a -= ANGLE_STEP;
		if (e->pl_a < 0)
			e->pl_a = 360 + e->pl_a;
	}
	//log_pl(e);
}

int		repaint(t_cub *e)
{
	update_world(e);
	render(e);
	mlx_put_image_to_window(e->mlx, e->win, e->main.img, 0, 0);
	if (e->map_visible)
		mlx_put_image_to_window(e->mlx, e->win, e->mp.img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/04 21:08:04 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ev_window_destroy(void)
{
	exit(0);
}

int		ev_key_press(int keycode, t_cub *e)
{
	//printf("keycode: %d\n", keycode);
	if (keycode == KEYCODE_ESC)
		exit(0);
	else if (keycode == KEYCODE_TAB)
		e->map_visible = !e->map_visible;
	else if (keycode == KEYCODE_A)
		e->pl_key_a = 1;
	else if (keycode == KEYCODE_W)
		e->pl_key_w = 1;
	else if (keycode == KEYCODE_S)
		e->pl_key_s = 1;
	else if (keycode == KEYCODE_D)
		e->pl_key_d = 1;
	else if (keycode == KEYCODE_LEFT)
		e->pl_key_left = 1;
	else if (keycode == KEYCODE_RIGHT)
		e->pl_key_right = 1;
	repaint(e);
	return (0);
}

int		ev_key_release(int keycode, t_cub *e)
{
	if (keycode == KEYCODE_A)
		e->pl_key_a = 0;
	else if (keycode == KEYCODE_W)
		e->pl_key_w = 0;
	else if (keycode == KEYCODE_S)
		e->pl_key_s = 0;
	else if (keycode == KEYCODE_D)
		e->pl_key_d = 0;
	else if (keycode == KEYCODE_LEFT)
		e->pl_key_left = 0;
	else if (keycode == KEYCODE_RIGHT)
		e->pl_key_right = 0;
	repaint(e);
	return (0);
}

int		ev_m(int button, int x, int y, t_cub *e)
{
	int color;

	(void)button;
	color = 0x0000FF00;
	mlx_pixel_put(e->mlx, e->win, x, y, color);
	//printf("x: %d, y: %d, button: %d\n", x, y, button);
	//repaint(e);
	return (0);
}

int		ev_mouse_motion(int x, int y, t_cub *e)
{
	ev_m(0, x, y, e);
	return (0);
}

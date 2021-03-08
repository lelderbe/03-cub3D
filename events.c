/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/08 09:50:29 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ev_window_destroy(void)
{
	exit(0);
}

int		ev_mouse_motion(int x, int y, t_cub *e)
{
	if (!MOUSE_ON)
		return (0);
	if (e->m_x != -1)
	{
		if (x < e->m_x)
			e->pl_a += ANGLE_STEP;
		if (x > e->m_x)
			e->pl_a -= ANGLE_STEP;
	}
	e->m_x = x;
	e->m_y = y;
	return (0);
}

int		ev_key_press(int keycode, t_cub *e)
{
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
	return (0);
}

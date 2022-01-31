/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/09 18:19:36 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ev_window_destroy(t_cub *e)
{
	return (exit_cub(e, 0));
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
	// printf("keycode: %d\n", keycode);
	if (keycode == KEYCODE_ESC)
		exit_cub(e, 0);
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
	else if (keycode == KEYCODE_1)
		e->walls_style = USE_ONE_COLOR;
	else if (keycode == KEYCODE_2)
		e->walls_style = USE_MANY_COLORS;
	else if (keycode == KEYCODE_3)
		e->walls_style = USE_TEXTURES;
	else if (keycode == KEYCODE_4)
		e->use_sprites = !e->use_sprites;
	else if (keycode == KEYCODE_5)
		e->wall_collision = !e->wall_collision;
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

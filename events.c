/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/16 13:25:24 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		event_window_destroy(t_vars *e)
{
	(void)e;
	printf("%s triggered\n", __FUNCTION__);
	exit (0);
	return (0);
}

int		event_window_create(t_vars *e)
{
	(void)e;
	printf("window create event\n");
	//repaint(e);
	return (0);
}

int		event_key_press(int keycode, t_vars *e)
{
	//int x;
	//int y;

	printf("keycode: %d\n", keycode);
	if (keycode == KEYCODE_ESC)
		exit (0);
	if (keycode == KEYCODE_A)
	{
		e->pl_x -= STEP;
		log_pl(e);
		if (e->pl_x < BODY / 2)
			e->pl_x = BODY / 2;
		log_pl(e);
	}
	if (keycode == KEYCODE_W)
	{
		e->pl_y -= STEP;
		log_pl(e);
		if (e->pl_y < BODY / 2)
			e->pl_y = BODY / 2;
		log_pl(e);
	}
	if (keycode == KEYCODE_S)
	{
		e->pl_y += STEP;
		log_pl(e);
		if (e->pl_y > e->height - BODY / 2)
			e->pl_y = e->height - BODY / 2;
		log_pl(e);
	}
	if (keycode == KEYCODE_D)
	{
		e->pl_x += STEP;
		log_pl(e);
		if (e->pl_x > e->width - BODY / 2)
			e->pl_x = e->width - BODY / 2;
		log_pl(e);
	}
	if (keycode == KEYCODE_LEFT)
	{
		e->pl_ang += 1;
		if (e->pl_ang >= 360)
			e->pl_ang -= 360;
		log_pl(e);
	}
	if (keycode == KEYCODE_RIGHT)
	{
		e->pl_ang -= 1;
		if (e->pl_ang < 0)
			e->pl_ang = 360 + e->pl_ang;
		//if (e->pl_ang <= -360)
		//	e->pl_ang += 360;
		log_pl(e);
	}

	repaint(e);
	return (0);
}

int		event_m(int button, int x, int y, t_vars *e)
{
	int color;

	(void)button;
	color = 0x0000FF00;
	mlx_pixel_put(e->mlx, e->win, x, y, color);
	//printf("x: %d, y: %d, button: %d\n", x, y, button);

	//repaint(e);

	return (0);
}

int		event_motion(int x, int y, t_vars *e)
{
	//int x;
	//int y;

	//(void)x;
	//(void)y;
	
	event_m(0, x, y, e);
	
	return (0);
}

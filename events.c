/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/17 13:43:33 by lelderbe         ###   ########.fr       */
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

void	check_pl_coords(t_vars *e)
{
	if (e->pl_x * SCALE < BODY / 2)
		e->pl_x = (BODY / 2) * 1.0 / SCALE;
	if (e->pl_y * SCALE < BODY / 2)
		e->pl_y = (BODY / 2) * 1.0 / SCALE;
}

int		event_key_press(int keycode, t_vars *e)
{
	double x;
	double y;

	printf("keycode: %d\n", keycode);
	if (keycode == KEYCODE_ESC)
		exit (0);
	if (keycode == KEYCODE_A)
	{
		x = cos((e->pl_ang - 90) / 180 * M_PI) * STEP;
		y = -sin((e->pl_ang - 90) / 180 * M_PI) * STEP;
		//e->pl_x -= STEP;
		e->pl_x -= x;
		e->pl_y -= y;
		log_pl(e);
		//if (e->pl_x < BODY / 2)
		//	e->pl_x = BODY / 2;
		if (e->pl_x * SCALE < BODY / 2)
			e->pl_x = (BODY / 2) * 1.0 / SCALE;
		if (e->pl_y * SCALE < BODY / 2)
			e->pl_y = (BODY / 2) * 1.0 / SCALE;
		log_pl(e);
	}
	if (keycode == KEYCODE_W)
	{
		//e->pl_y -= STEP;
		x = cos((e->pl_ang - 0) / 180 * M_PI) * STEP;
		y = -sin((e->pl_ang - 0) / 180 * M_PI) * STEP;
		e->pl_x += x;
		e->pl_y += y;
		log_pl(e);
		//if (e->pl_y < BODY / 2)
		//	e->pl_y = BODY / 2;
		if (e->pl_x * SCALE < BODY / 2)
			e->pl_x = (BODY / 2) * 1.0 / SCALE;
		if (e->pl_y * SCALE < BODY / 2)
			e->pl_y = (BODY / 2) * 1.0 / SCALE;
		log_pl(e);
	}
	if (keycode == KEYCODE_S)
	{
		e->pl_y += STEP;
		log_pl(e);
		//if (e->pl_y > e->height - BODY / 2)
		//	e->pl_y = e->height - BODY / 2;
		if (e->pl_y * SCALE > e->height - BODY / 2)
			e->pl_y = (e->height - BODY / 2) * 1.0 / SCALE;
		log_pl(e);
	}
	if (keycode == KEYCODE_D)
	{
		//e->pl_x += STEP;
		x = cos((e->pl_ang + 90) / 180 * M_PI) * STEP;
		y = -sin((e->pl_ang + 90) / 180 * M_PI) * STEP;
		e->pl_x -= x;
		e->pl_y -= y;
		log_pl(e);
		//if (e->pl_x > e->width - BODY / 2)
		//	e->pl_x = e->width - BODY / 2;
		if (e->pl_x * SCALE > e->width - BODY / 2)
			e->pl_x = (e->width - BODY / 2) * 1.0 / SCALE;
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

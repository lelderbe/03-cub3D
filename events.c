/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/27 15:53:41 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		event_window_destroy(t_cub *e)
{
	(void)e;
	printf("%s triggered\n", __FUNCTION__);
	exit (0);
	return (0);
}

int		event_window_create(t_cub *e)
{
	(void)e;
	printf("window create event\n");
	//repaint(e);
	return (0);
}

void	check_pl_coords(t_cub *e)
{
	(void)e;
	//if (e->pl_x * SCALE < BODY / 2)
	//	e->pl_x = (BODY / 2) * 1.0 / SCALE;
	//if (e->pl_y * SCALE < BODY / 2)
	//	e->pl_y = (BODY / 2) * 1.0 / SCALE;
	//if (e->pl_x * SCALE > e->width - BODY / 2)
	//		e->pl_x = (e->width - BODY / 2) * 1.0 / SCALE;
	//if (e->pl_y * SCALE > e->height - BODY / 2)
	//		e->pl_y = (e->height - BODY / 2) * 1.0 / SCALE;
/*	
	if (e->pl_x * SCALE < BODY / 2)
		e->pl_x = (BODY / 2) * 1.0 / SCALE;
	if (e->pl_y * SCALE < BODY / 2)
		e->pl_y = (BODY / 2) * 1.0 / SCALE;
	if (e->pl_x * SCALE > e->width - BODY / 2)
			e->pl_x = (e->width - BODY / 2) * 1.0 / SCALE;
	if (e->pl_y * SCALE > e->height - BODY / 2)
			e->pl_y = (e->height - BODY / 2) * 1.0 / SCALE;
*/
}

void	pl_check_and_move(t_cub *e, double dx, double dy)
{
	double x;
	double y;
	//int sign;

	//sign = dx < 0 ? -1 : 1;

	x = e->pl_x + dx;
	if (dx > 0)
		x += BODY / 2;
	else
		x -= BODY / 2;
	y = e->pl_y;
	printf("x: %6.2f, y: %6.2f\n", x, y);

	if (e->map[(int)y][(int)x] == MAP_WALL)
	{
		if (dx > 0)
			x = (int)(x) - BODY / 2;
		else
			x = (int)(x + 1) + BODY / 2;
	}
	else
	{
		x = e->pl_x + dx;
	}

	y = e->pl_y + dy;
	if (dy > 0)
		y += BODY / 2;
	else
		y -= BODY / 2;
	printf("x: %6.2f, y: %6.2f\n", x, y);

	if (e->map[(int)y][(int)x] == MAP_WALL)
	{
		if (dy > 0)
			y = (int)(y) - BODY / 2;
		else
			y = (int)(y + 1) + BODY / 2;
	}
	else
	{
		y = e->pl_y + dy;
	}
	
	printf("final x: %6.2f, y: %6.2f\n", x, y);

	e->pl_x = x;
	e->pl_y = y;
}

int		event_key_press(int keycode, t_cub *e)
{
	double dx;
	double dy;

	(void)dx;
	(void)dy;
	printf("keycode: %d\n", keycode);
	if (keycode == KEYCODE_ESC)
		exit (0);
	if (keycode == KEYCODE_TAB)
		e->map_visible = !e->map_visible;
	if (keycode == KEYCODE_A)
	{
		e->pl_a = 1;
		/*
		dx = cos((e->pl_ang + 90) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang + 90) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		log_pl(e);
		*/
	}
	if (keycode == KEYCODE_W)
	{
		e->pl_w = 1;
		/*
		dx = cos((e->pl_ang - 0) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 0) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		log_pl(e);
		*/
	}
	if (keycode == KEYCODE_S)
	{
		e->pl_s = 1;
		/*
		dx = cos((e->pl_ang - 180) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 180) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		log_pl(e);
		*/
	}
	if (keycode == KEYCODE_D)
	{
		e->pl_d = 1;
		/*
		dx = cos((e->pl_ang - 90) / 180 * M_PI) * STEP;
		dy = -sin((e->pl_ang - 90) / 180 * M_PI) * STEP;
		//e->pl_x += dx;
		//e->pl_y += dy;
		log_pl(e);
		pl_check_and_move(e, dx, dy);
		//check_pl_coords(e);
		log_pl(e);
		*/
	}
	if (keycode == KEYCODE_LEFT)
	{
		e->pl_left = 1;
		/*
		e->pl_ang += ANGLE_STEP;
		if (e->pl_ang >= 360)
			e->pl_ang -= 360;
		log_pl(e);
		*/
	}
	if (keycode == KEYCODE_RIGHT)
	{
		e->pl_right = 1;
		/*
		e->pl_ang -= ANGLE_STEP;
		if (e->pl_ang < 0)
			e->pl_ang = 360 + e->pl_ang;
		//if (e->pl_ang <= -360)
		//	e->pl_ang += 360;
		log_pl(e);
		*/
	}

	repaint(e);
	return (0);
}

int		event_key_release(int keycode, t_cub *e)
{

	if (keycode == KEYCODE_A)
	{
		e->pl_a = 0;
	}
	if (keycode == KEYCODE_W)
	{
		e->pl_w = 0;
	}
	if (keycode == KEYCODE_S)
	{
		e->pl_s = 0;
	}
	if (keycode == KEYCODE_D)
	{
		e->pl_d = 0;
	}
	if (keycode == KEYCODE_LEFT)
	{
		e->pl_left = 0;
	}
	if (keycode == KEYCODE_RIGHT)
	{
		e->pl_right = 0;
	}

	repaint(e);
	return (0);
}

int		event_m(int button, int x, int y, t_cub *e)
{
	int color;

	(void)button;
	color = 0x0000FF00;
	mlx_pixel_put(e->mlx, e->win, x, y, color);
	//printf("x: %d, y: %d, button: %d\n", x, y, button);

	//repaint(e);

	return (0);
}

int		event_motion(int x, int y, t_cub *e)
{
	//int x;
	//int y;

	//(void)x;
	//(void)y;
	
	event_m(0, x, y, e);
	
	return (0);
}

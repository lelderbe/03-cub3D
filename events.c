/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/03 14:46:48 by lelderbe         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_vars *e, int x, int y, int color)
{
    char    *dst;

    dst = e->addr + (y * e->line_length + x * (e->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		event_key_press(int keycode, t_vars *e)
{
	int x;
	int y;

	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit (0);
	if (keycode == 0)
	{
		e->pl_x -= STEP;
		log_pl(e);
		if (e->pl_x < BODY / 2)
			e->pl_x = BODY / 2;
		log_pl(e);
	}
	if (keycode == 13)
	{
		e->pl_y -= STEP;
		log_pl(e);
		if (e->pl_y < BODY / 2)
			e->pl_y = BODY / 2;
		log_pl(e);
	}
	if (keycode == 1)
	{
		e->pl_y += STEP;
		log_pl(e);
		if (e->pl_y > e->height - BODY / 2)
			e->pl_y = e->height - BODY / 2;
		log_pl(e);
	}
	if (keycode == 2)
	{
		e->pl_x += STEP;
		log_pl(e);
		if (e->pl_x > e->width - BODY / 2)
			e->pl_x = e->width - BODY / 2;
		log_pl(e);
	}

	e->img = mlx_new_image(e->mlx, e->width, e->height);

    e->addr = mlx_get_data_addr(e->img, &e->bits_per_pixel, &e->line_length,
                                 &e->endian);
	printf("addr: %p\n", e->addr);
	printf("bits_per_pixel: %d\n", e->bits_per_pixel);
	printf("line_length: %d\n", e->line_length);
	printf("endian: %d\n", e->endian);
	x = 0;
	while (x < e->width)
	{
		y = 0;
		while (y < e->height)
		{
		    //my_mlx_pixel_put(e, x, y, 0x008F0000);
		    my_mlx_pixel_put(e, x, y, keycode);
			y++;
		}
		x++;
	}

    mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);

	repaint(e);

	return (0);
}

int		event_m(int button, int x, int y, t_vars *e)
{
	int color;

	(void)button;
	color = 0x0000FF00;
	mlx_pixel_put(e->mlx, e->win, x, y, color);
	printf("x: %d, y: %d, button: %d\n", x, y, button);

	repaint(e);

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

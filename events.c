/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/02 16:41:23 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		window_destroy_event(t_vars *e)
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

int		key_press_event(int keycode, t_vars *e)
{
	unsigned int x;
	unsigned int y;

	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit (0);
	
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

	return (0);
}

int		m_event(int button, int x, int y, t_vars *e)
{
	int color;

	(void)button;
	color = 0x0000FF00;
	mlx_pixel_put(e->mlx, e->win, x, y, color);
	printf("x: %d, y: %d, button: %d\n", x, y, button);

	return (0);
}

int		motion_event(int x, int y, t_vars *e)
{
	//int x;
	//int y;

	//(void)x;
	//(void)y;
	
	m_event(0, x, y, e);
	
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:51:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/02 15:54:10 by lelderbe         ###   ########.fr       */
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

int		key_press_event(int keycode, t_vars *e)
{
	(void)e;
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		exit (0);
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

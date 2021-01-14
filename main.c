/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:12:35 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/14 12:53:58 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		m_event(int button, int x, int y, t_params *e)
{
	int color;


	//printf("e addr EVENT: %p\n", e);
	(void)button;
	color = 0xFFFFFF;
	mlx_pixel_put(e->mlx, e->window, x, y, color);
	printf("x: %d, y: %d, button: %d\n", x, y, button);

	return (0);
}

int		motion_event(int x, int y, t_params *e)
{
	//int x;
	//int y;

	//(void)x;
	//(void)y;
	//printf("e addr: %p\n", e);
	
	//printf("e->mlx addr: %p\n", e->mlx);
	//printf("before\n");
	//mlx_mouse_get_pos(e->window, &x, &y);
	//printf("after\n");
	m_event(0, x, y, e);
	
	return (0);
}

void	init_params(t_params *e)
{
	e->mlx = 0;
	e->window = 0;
}

int		main(int argc, char **argv)
{
	t_params	e;
	(void)argc;
	(void)argv;

	init_params(&e);
	printf("e addr: %p\n", &e);
	e.mlx = mlx_init();
	e.window = mlx_new_window(e.mlx, 640, 480, "cub3D");
	if (!e.window)
	{
		printf("error creating window ( \n");
		return (-1);
	}
	printf("e->mlx addr: %p\n", e.mlx);
	printf("e->window addr: %p\n", e.window);
	printf("e addr: %p\n", &e);
	mlx_clear_window(e.mlx, e.window);
	mlx_mouse_hook(e.window, &m_event, &e); 
	printf("e addr 2: %p\n", &e);
	mlx_hook(e.window, 6, 1L<<6, &motion_event, &e);
	mlx_loop(e.mlx);
	return (0);
}

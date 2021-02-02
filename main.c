/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:58:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/02 16:28:39 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(t_vars *e)
{
	e->cub_filename = 0;
	e->save_option = 0;
	e->mlx = 0;
	e->win = 0;
	e->img = 0;
	e->addr = 0;
	e->bits_per_pixel = 0;
	e->line_length = 0;
	e->endian = 0;
}

int		hook_events(t_vars *e)
{
	mlx_mouse_hook(e->win, m_event, e); 
	mlx_hook(e->win, 6, 1L<<6, motion_event, e);
	mlx_hook(e->win, 2, 1L<<0, key_press_event, e);
	mlx_hook(e->win, 17, 0L<<0, window_destroy_event, e);
	return (OK);
}

int		main(int argc, char **argv)
{
	t_vars	e;

	init_vars(&e);
	// parse params
	if (parse_params(argc, argv, &e) == FAIL)
		return (-1);
	// parse .cub-file
	if (parse_cub_file(&e) == FAIL)
		return (-1);
	// mlx init
	if (!(e.mlx = mlx_init()))
		return (-1);
	// window create
	if (!(e.win = mlx_new_window(e.mlx, e.width, e.height, APP_NAME)))
	{
		printf("error creating window ( \n");
		return (-1);
	}

	if (e.save_option)
	{
		// save bmp and exit
		printf("will save BMP here\n");
	}
	//mlx_clear_window(e.mlx, e.window);
	// hook events create
	hook_events(&e);
	e.img = mlx_new_image(e.mlx, e.width, e.height);
	// game start
	mlx_loop(e.mlx);
	return (0);
}

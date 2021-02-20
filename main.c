/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:58:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/20 14:30:53 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(t_vars *e)
{
	ft_memset(e, 0, sizeof(*e));
	/*
	e->cub_filename = 0;
	e->save_option = 0;
	e->mlx = 0;
	e->win = 0;
	e->img = 0;
	e->addr = 0;
	e->bits_per_pixel = 0;
	e->line_length = 0;
	e->endian = 0;
	*/
}

int		hook_events(t_vars *e)
{
	mlx_mouse_hook(e->win, event_m, e); 
	mlx_hook(e->win, EV_MOTION_NOTIFY, MASK_POINTER_MOTION, event_motion, e);
	mlx_hook(e->win, EV_KEY_PRESS, MASK_KEY_PRESS, event_key_press, e);
	mlx_hook(e->win, EV_KEY_RELEASE, MASK_KEY_RELEASE, event_key_release, e);
	mlx_hook(e->win, EV_CREATE_NOTIFY, 0, event_window_create, e);
	mlx_hook(e->win, EV_DESTROY_NOTIFY, MASK_NO_EVENT, event_window_destroy, e);
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
	log_map2(&e);
	log_pl(&e);

	// mlx init
	if (!(e.mlx = mlx_init()))
		return (-1);
	// window create
	if (!(e.win = mlx_new_window(e.mlx, e.width, e.height, APP_NAME)))
	{
		printf("error creating window ( \n");
		return (-1);
	}

	repaint(&e);

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
	//mlx_loop_hook(e.mlx, repaint, &e);
	mlx_loop(e.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:58:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 11:39:55 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_cub *e)
{
	ft_memset(e, 0, sizeof(*e));
	e->wall_color = DEF_WALL_COLOR;
	e->floor_color = DEF_FLOOR_COLOR;
	e->ceil_color = DEF_CEIL_COLOR;
}

static void	hook_events(t_cub *e)
{
	mlx_mouse_hook(e->win, event_m, e); 
	mlx_hook(e->win, EV_MOTION_NOTIFY, MASK_POINTER_MOTION, event_motion, e);
	mlx_hook(e->win, EV_KEY_PRESS, MASK_KEY_PRESS, event_key_press, e);
	mlx_hook(e->win, EV_KEY_RELEASE, MASK_KEY_RELEASE, event_key_release, e);
	mlx_hook(e->win, EV_CREATE_NOTIFY, 0, event_window_create, e);
	mlx_hook(e->win, EV_DESTROY_NOTIFY, MASK_NO_EVENT, event_window_destroy, e);
}

static void	init_mlx(t_cub *e)
{
	if (!(e->mlx = mlx_init()))
		err_exit(ERR_MLX_INIT);
	if (!(e->win = mlx_new_window(e->mlx, e->width, e->height, APP_NAME)))
		err_exit(ERR_MLX_WINDOW);
	// main img prepare
	e->main.img = mlx_new_image(e->mlx, e->width, e->height);
	e->main.addr = mlx_get_data_addr(e->main.img,
				&e->main.bpp, &e->main.len, &e->main.endian);
	e->main.width = e->width;
	e->main.height = e->height;
	log_img(e->main.addr, e->main.bpp, e->main.len, e->main.endian);
	// mini-map img prepare
	e->mp.img = mlx_new_image(e->mlx, e->width, e->height);
	e->mp.addr = mlx_get_data_addr(e->mp.img,
				&e->mp.bpp, &e->mp.len, &e->mp.endian);
	e->mp.width = e->width;
	e->mp.height = e->height;
	log_img(e->mp.addr, e->mp.bpp, e->mp.len, e->mp.endian);
	textures_load(e);
}

int			main(int argc, char **argv)
{
	t_cub	e;

	init_game(&e);
	parse_arguments(argc, argv, &e);
	parse_cub_file(&e);
	log_map2(&e);
	log_pl(&e);
	init_mlx(&e);
	repaint(&e);
	if (e.save_option)
	{
		save_img_to_bmp(&e.main);
		exit (0);
	}
	hook_events(&e);
	// game start
	//mlx_loop_hook(e.mlx, repaint, &e);
	mlx_loop(e.mlx);
	return (0);
}

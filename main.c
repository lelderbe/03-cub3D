/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:58:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/27 20:40:50 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(t_vars *e)
{
	ft_memset(e, 0, sizeof(*e));
	e->wall_color = DEF_WALL_COLOR;
	e->floor_color = DEF_FLOOR_COLOR;
	e->ceil_color = DEF_CEIL_COLOR;
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
	parse_params(argc, argv, &e);
	parse_cub_file(&e);
	log_map2(&e);
	log_pl(&e);
	if (!(e.mlx = mlx_init()))
		err_exit(ERR_MLX_INIT);
	if (!(e.win = mlx_new_window(e.mlx, e.width, e.height, APP_NAME)))
		err_exit(ERR_MLX_WINDOW);
	texture_load(&e);
	// window img prepare
	e.main.img = mlx_new_image(e.mlx, e.width, e.height);
	e.main.addr = mlx_get_data_addr(e.main.img, &e.main.bpp, &e.main.len, &e.main.endian);
	log_img(e.main.addr, e.main.bpp, e.main.len, e.main.endian);
	// 2d map img prepare
	e.mp.img = mlx_new_image(e.mlx, e.width, e.height);
	e.mp.addr = mlx_get_data_addr(e.mp.img, &e.mp.bpp, &e.mp.len, &e.mp.endian);
	log_img(e.mp.addr, e.mp.bpp, e.mp.len, e.mp.endian);
	repaint(&e);
	if (e.save_option)
	{
		// save bmp and exit
		printf("will save BMP here\n");
	}
	//mlx_clear_window(e.mlx, e.window);
	// hook events create
	hook_events(&e);
	// game start
	//mlx_loop_hook(e.mlx, repaint, &e);
	mlx_loop(e.mlx);
	return (0);
}

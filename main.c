/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:58:19 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/10 13:50:31 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub(t_cub *e)
{
	ft_bzero(e, sizeof(*e));
	e->w_clr = DEF_WALL_COLOR;
	e->f_clr = DEF_FLOOR_COLOR;
	e->c_clr = DEF_CEIL_COLOR;
	e->walls_style = USE_TEXTURES;
	e->wall_collision = WALL_COLLISION;
	e->use_sprites = USE_SPRITES;
	mlx_get_screen_size(&e->sys_width, &e->sys_height);
	e->m_x = -1;
	e->m_y = -1;
}

static void	hook_events(t_cub *e)
{
	mlx_hook(e->win, EV_KEY_PRESS, MASK_KEY_PRESS, ev_key_press, e);
	mlx_hook(e->win, EV_KEY_RELEASE, MASK_KEY_RELEASE, ev_key_release, e);
	mlx_hook(e->win, EV_DESTR_NOTIFY, MASK_NO_EVENT, ev_window_destroy, e);
	mlx_hook(e->win, EV_MOTION_NOTIFY, MASK_PTR_MOTION, ev_mouse_motion, e);
}

static void	init_mlx(t_cub *e)
{
	if (!(e->mlx = mlx_init()))
		exit_cub(e, ERR_MLX_INIT);
	if (!(e->win = mlx_new_window(e->mlx, e->width, e->height, APP_NAME)))
		exit_cub(e, ERR_MLX_WINDOW);
	e->main.img = mlx_new_image(e->mlx, e->main.w, e->main.h);
	e->main.addr = mlx_get_data_addr(e->main.img,
				&e->main.bpp, &e->main.len, &e->main.endian);
	e->mp.img = mlx_new_image(e->mlx, e->width, e->height);
	e->mp.addr = mlx_get_data_addr(e->mp.img,
				&e->mp.bpp, &e->mp.len, &e->mp.endian);
	e->mp.w = e->width;
	e->mp.h = e->height;
	textures_load(e);
}

int			main(int argc, char **argv)
{
	t_cub	e;

	init_cub(&e);
	parse_arguments(argc, argv, &e);
	parse_cub_file(&e);
	init_mlx(&e);
	repaint(&e);
	if (e.save_option)
	{
		save_img_to_bmp(&e, &e.main, e.of);
		exit_cub(&e, 0);
	}
	hook_events(&e);
	mlx_loop_hook(e.mlx, repaint, &e);
	mlx_loop(e.mlx);
	free_resources(&e);
	return (0);
}

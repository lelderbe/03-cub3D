/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2d_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:56:33 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/04 21:24:05 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		clear_2d_map_window(t_cub *e)
{
	int y;
	int x;

	if (!e->map_visible)
		return ;
	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x < e->width)
		{
			img_pixel_put(&e->mp, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
}

void		display_2d_sprites(int x, int y, t_cub *e)
{
	int i;
	int j;
	int border;

	border = 1;
	j = 0 + border;
	while (j < MAP_TILE - border)
	{
		i = 0 + border;
		while (i < MAP_TILE - border)
		{
			if (x * MAP_TILE + i < e->width && y * MAP_TILE + j < e->height)
				img_pixel_put(&e->mp,
						x * MAP_TILE + i, y * MAP_TILE + j, 0x00FFFF00);
			i++;
		}
		j++;
	}
}

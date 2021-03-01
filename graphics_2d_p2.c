/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_2d_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:56:33 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/01 14:13:19 by lelderbe         ###   ########.fr       */
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
			// TODO: optimize
			img_pixel_put(&e->mp, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
}

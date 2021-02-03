/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:15:32 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/03 13:35:28 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	repaint(t_vars *e)
{
	display_map(e);
}

void	display_map(t_vars *e)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			// print pixel
			//printf("%c ", e->map[y][x]);
			if (e->map[y][x] == '1')
			{
				j = 0;
				while (j < SCALE)
				{
					i = 0;
					while (i < SCALE)
					{
						mlx_pixel_put(e->mlx, e->win, x * SCALE + i, y * SCALE + j, 0x00FFFFFF);
						i++;
					}
					j++;
				}
			}
			/*
			if (e->map[y][x] == 'N')
			{
				j = SCALE / 2 - BODY;
				while (j < SCALE / 2 + BODY)
				{
					i = SCALE / 2 - BODY;
					while (i < SCALE / 2 + BODY)
					{
						mlx_pixel_put(e->mlx, e->win, x * SCALE + i, y * SCALE + j, 0x0000FF00);
						i++;
					}
					j++;
				}
			}
			*/
			x++;
		}

		//printf("%s\n", e->map[i]);
		y++;
	}
	j = - BODY / 2;
	while (j < BODY / 2)
	{
		i = - BODY / 2;
		while (i < BODY / 2)
		{
			mlx_pixel_put(e->mlx, e->win, e->pl_x + i, e->pl_y + j, 0x0000FF00);
			i++;
		}
		j++;
	}
}

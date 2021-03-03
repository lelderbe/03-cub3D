/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:20:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/03 19:17:39 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
static void	d(t_spr *s, int x, int y, double step)
{

}
*/

static int	get_color_sp(t_cub *e, int dx, int dy)
{
	unsigned	color;
	int			addr;
	t_img		sp;

	sp = e->sprite;
	//color = e->wall_color;
	//color = USE_MANY_COLORS ? e->color : color;
	addr = dy * sp.len + dx * (sp.bpp / 8);
	color = *((unsigned int*)(sp.addr + addr));
	//color = USE_FOG ? (int)(255 / (1 + d * d * 0.1)) : color;
	return (color);
}

static void	disp(t_cub *e, t_spr *s, double d, double ang)
{
	int	i;
	int	height;
	double	step;
	double	dx;
	double dy;
	int center;
	int y;
	unsigned color;

	(void)s;
	height = (int)(e->dpp / d);
	dy = 0;
	step = 1.0 * e->sprite.height / height;
	if (height >= e->height)
	{
		dy = step * (height - e->height) / 2;
		height = e->height - 1;
	}
	i = 0;
	while (i < e->width)
	{
		//printf("z[%d]: %6.2f\n", i, e->pl_x - e->atans[i]);
		if (e->pl_a - e->atans[i] < ang)
			break ;
		i++;
	}
	center = i;
	printf("center: %d, d: %6.2f, ang: %6.2f, pl_a: %6.2f\n", center, d, ang, e->pl_a);
	if (center == e->width || i == 0)
		return ;
	y = - height / 2;
	while (y < height / 2)
	{
		i = - height / 2;
		dx = 0;
		while (i < height / 2)
		{
			if (center + i >= 0 && center + i < e->width &&
					e->half_h + y >= 0 && e->half_h + y < e->height)
			{
				//img_pixel_put(&e->main, dx + i, e->half_h + y, 0x00000000);
				color = get_color_sp(e, (int)dx, (int)dy);
				if (color != TRANSPARENT_COLOR)
					img_pixel_put(&e->main, center + i, e->half_h + y, color);
			}
			i++;
			dx = dx + step;
		}
		y++;
		dy = dy + step;
	}
	
}

void		draw_sprites(t_cub *e)
{
	double	d;
	double	ang;
	double	dx;
	double	dy;
	int		i;

	i = 0;
	while (e->s[i])
	{
		dx = e->s[i]->x - e->pl_x;
		dy = -(e->s[i]->y - e->pl_y);
		d = sqrt(dx * dx + dy * dy);
		//ang = dy / dx * 180 / M_PI;
		ang = atan2(dy, dx) * 180 / M_PI;
		printf("atan: %6.2f, atan ang: %6.2f\n", atan2(dy, dx), atan2(dy, dx) * 180 / M_PI);
		//printf("dx: %6.2f, dy: %6.2f, d: %6.2f, ang: %6.2f\n", dx, dy, d, ang);
		disp(e, e->s[i], d, ang);
		i++;

	}

}

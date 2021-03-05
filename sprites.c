/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:20:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/05 16:25:53 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sprite(t_cub *e, double d)
{
	int			y;
	int			x;
	double		dx;
	unsigned	color;

	y = -(e->s_h / 2);
	while (y < e->s_h / 2)
	{
		x = -(e->s_w / 2);
		dx = e->s_dx;
		while (x < e->s_w / 2)
		{
			if (e->s_c + x >= 0 && e->s_c + x < e->width && e->half_h + y >= 0
					&& e->half_h + y < e->height && e->z[e->s_c + x] > d)
			{
				color = get_color_sp(e, (int)dx, (int)e->s_dy);
				if (color != TRANSPARENT_COLOR)
					img_pixel_put(&e->main, e->s_c + x, e->half_h + y, color);
			}
			x++;
			dx = dx + e->s_st_x;
		}
		y++;
		e->s_dy = e->s_dy + e->s_st_y;
	}
}

static void	disp(t_cub *e, t_spr *s, double d, double ang)
{
	(void)s;
	e->s_st_y = 1.0 * e->sprite.height / e->s_h;
	e->s_st_x = 1.0 * e->sprite.width / e->s_w;
	if (e->s_h >= e->height)
	{
		e->s_dy = e->s_st_y * (e->s_h - e->height) / 2;
		e->s_h = e->height - 1;
	}
	if (e->s_w >= e->width)
	{
		e->s_dx = e->s_st_y * (e->s_w - e->width) / 2;
		e->s_w = e->width - 1;
	}
	e->s_c = 0;
	while (e->s_c < e->width)
	{
		if (e->pl_a - e->atans[e->s_c] < ang)
			break ;
		e->s_c++;
	}
	if (e->s_c == e->width || e->s_c == 0)
		return ;
	draw_sprite(e, d);
}

static void	sort_sprites(t_cub *e)
{
	int		count;
	int		i;
	int		j;
	t_spr	*s;

	count = e->sc;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (e->s[j]->d < e->s[j + 1]->d)
			{
				s = e->s[j];
				e->s[j] = e->s[j + 1];
				e->s[j + 1] = s;
			}
			j++;
		}
		i++;
	}
}

static void	calc_sprite_distances(t_cub *e)
{
	int		i;
	double	dx;
	double	dy;
	double	ang;

	i = 0;
	while (e->s[i])
	{
		dx = e->s[i]->x - e->pl_x;
		dy = -(e->s[i]->y - e->pl_y);
		e->s[i]->d = hypot(dx, dy);
		ang = atan2(dy, dx) * 180 / M_PI;
		ang = ang - e->pl_a > 180 ? ang - 360 : ang;
		ang = ang - e->pl_a < -180 ? ang + 360 : ang;
		e->s[i]->ang = ang;
		i++;
	}
}

void		draw_sprites(t_cub *e)
{
	int		i;

	calc_sprite_distances(e);
	sort_sprites(e);
	i = 0;
	while (e->s[i])
	{
		e->s_dy = 0;
		e->s_dx = 0;
		e->s_h = (int)(e->dpp / e->s[i]->d);
		e->s_w = e->s_h;
		if (e->s[i]->d > 1.0 / 2)
			disp(e, e->s[i], e->s[i]->d, e->s[i]->ang);
		i++;
	}
}

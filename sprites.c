/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:20:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/12 11:27:14 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sprite(t_cub *e, int col, double d)
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
			if (col + x >= 0 && col + x < e->main.w && e->main.half_h + y >= 0
					&& e->main.half_h + y < e->main.h && e->z[col + x] > d)
			{
				color = get_color_sp(e, (int)dx, (int)e->s_dy);
				if (color != TRANSPARENT_COLOR)
					img_pixel_put(&e->main, col + x, e->main.half_h + y, color);
			}
			x++;
			dx = dx + e->s_st_x;
		}
		y++;
		e->s_dy = e->s_dy + e->s_st_y;
	}
}

static void	disp(t_cub *e, double d, double ang)
{
	e->s_st_y = 1.0 * e->sprite.h / e->s_h;
	e->s_st_x = 1.0 * e->sprite.w / e->s_w;
	if (e->s_h >= e->main.h)
	{
		e->s_dy = e->s_st_y * (e->s_h - e->main.h) / 2;
		e->s_h = e->main.h - 1;
	}
	if (e->s_w >= e->main.w)
	{
		e->s_dx = e->s_st_y * (e->s_w - e->main.w) / 2;
		e->s_w = e->main.w - 1;
	}
	e->s_c = 0;
	while (e->s_c < e->main.w)
	{
		if (e->pl_a - e->atans[e->s_c] < ang)
			break ;
		e->s_c++;
	}
	if (e->s_c == e->main.w || e->s_c == 0)
		return ;
	draw_sprite(e, e->s_c, d);
}

static void	sort_sprites(t_cub *e)
{
	int		count;
	int		i;
	int		j;
	t_spr	*s;

	count = e->s_count;
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

void		display_3d_sprites(t_cub *e)
{
	int		i;

	if (!e->use_sprites)
		return ;
	calc_sprite_distances(e);
	sort_sprites(e);
	i = 0;
	while (e->s[i])
	{
		e->s_dy = 0;
		e->s_dx = 0;
		e->s[i]->d = e->s[i]->d * cos_a(e->s[i]->ang - e->pl_a);
		e->s_h = (int)(e->dpp / e->s[i]->d);
		e->s_w = e->s_h;
		if (e->s[i]->d > 1.0 / 2)
			disp(e, e->s[i]->d, e->s[i]->ang);
		i++;
	}
}

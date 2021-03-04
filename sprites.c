/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:20:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/04 20:14:32 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*
static void	display_3d_spr_col(t_cub *e, int column, int dx, double d)
{
	int		i;
	int		height;
	double	step;
	int		dx;
	double	dy;

	height = (int)(e->dpp / d);
	dy = 0;
	step = 1.0 * e->sprite.height / height;
	if (height >= e->height)
	{
		dy = step * (height - e->height) / 2;
		height = e->height - 1;
	}
	//dx = (int)(e->sprite.width * e->hit);
	i = -height / 2;
	while (i < height / 2)
	{
		img_pixel_put(&e->main, column, e->height / 2 + i,
										get_colori_sp(e, dx, floor(dy)));
		dy = dy + step;
		i++;
	}
}
*/

/*
static void	disp2(t_cub *e, t_spr *s, double d, double ang)
{
	int	i;
	int	height;
	int	width;
	double	step;
	double	dx;
	double	dx0;
	double dy;
	int center;
	int y;
	unsigned color;

	(void)s;

	i = 0;


	height = (int)(e->dpp / d);
	dy = 0;
	dx0 = 0;
	step = 1.0 * e->sprite.height / height;
	//step_x = 1.0 * e->sprite.width / t;
	if (height >= e->height)
	{
		dy = step * (height - e->height) / 2;
		dx0 = step * ( - e->width) / 2;
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
		dx = dx0;
		while (i < width / 2)
		{
			if (center + i >= 0 && center + i < e->width &&
					e->half_h + y >= 0 && e->half_h + y < e->height)
			{
				//img_pixel_put(&e->main, dx + i, e->half_h + y, 0x00000000);
				color = get_color_sp(e, (int)dx, (int)dy);
				//if (color != TRANSPARENT_COLOR)
					img_pixel_put(&e->main, center + i, e->half_h + y, color);
			}
			i++;
			dx = dx + step;
		}
		y++;
		dy = dy + step;
	}
	
}
*/
static void	disp(t_cub *e, t_spr *s, double d, double ang)
{
	int	i;
	int	height;
	int width;
	double	step;
	double	step_x;
	double	dx;
	double	dx0;
	double dy;
	int center;
	int y;
	unsigned color;

	(void)s;
	height = (int)(e->dpp / d);
	width = height;
	dy = 0;
	dx0 = 0;
	step = 1.0 * e->sprite.height / height;
	step_x = 1.0 * e->sprite.width / width;
	if (height >= e->height)
	{
		dy = step * (height - e->height) / 2;
		height = e->height - 1;
	}
	if (width >= e->width)
	{
		dx0 = step * (width - e->width) / 2;
		width = e->width - 1;
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
		i = - width / 2;
		dx = dx0;
		while (i < width / 2)
		{
			if (center + i >= 0 && center + i < e->width &&
					e->half_h + y >= 0 && e->half_h + y < e->height &&
					e->z[center + i] > d)
			{
				color = get_color_sp(e, (int)dx, (int)dy);
				if (color != TRANSPARENT_COLOR)
					img_pixel_put(&e->main, center + i, e->half_h + y, color);
			}
			i++;
			dx = dx + step_x;
		}
		y++;
		dy = dy + step;
	}
}

static void	sort_sprites(t_cub *e)
{
	int count;
	int i;
	int j;
	t_spr *s;
	
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
	int	i;
	double	dx;
	double	dy;

	i = 0;
	while (e->s[i])
	{
		dx = e->s[i]->x - e->pl_x;
		dy = -(e->s[i]->y - e->pl_y);
		e->s[i]->d = hypot(dx, dy);
		i++;	
	}
}

void		draw_sprites(t_cub *e)
{
	double	d;
	double	ang;
	double	dx;
	double	dy;
	int		i;

	calc_sprite_distances(e);
	sort_sprites(e);
	i = 0;
	while (e->s[i])
	{
		dx = e->s[i]->x - e->pl_x;
		dy = -(e->s[i]->y - e->pl_y);
		d = e->s[i]->d;
		ang = atan2(dy, dx) * 180 / M_PI;
		ang = ang - e->pl_a > 180 ? ang - 360 : ang;
		ang = ang - e->pl_a < -180 ? ang + 360 : ang;
		//printf("atan: %6.2f, pl_x: %6.2f, pl_y: %6.2f, s_x: %6.2f, s_y: %6.2f\n",
		//	atan2(dy, dx) * 180 / M_PI, e->pl_x, e->pl_y, e->s[i]->x, e->s[i]->y);
		//printf("dx: %6.2f, dy: %6.2f, d: %6.2f, ang: %6.2f\n", dx, dy, d, ang);
		if (d > 1.0 / 2)
			disp(e, e->s[i], d, ang);
		i++;
	}
}

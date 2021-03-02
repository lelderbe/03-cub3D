/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:39:50 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 11:48:01 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}
/*
int		add_shade(double d, int color)
{
	return (create_trgb(
			get_t,
			(int)(get_r - get_r * d),
			(int)(get_g - get_g * d),
			(int)(get_b - get_b * d)
			));
}
*/
void	img_pixel_put(t_img *img, double x, double y, int color)
{
	int		xx;
	int		yy;
    char    *dst;

	xx = (int)(x);
	yy = (int)(y);
    dst = img->addr + (yy * img->len + xx * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

void	textures_load(t_cub *e)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (e->w[i].file)
		{
			if (!(e->w[i].img = mlx_xpm_file_to_image(
					e->mlx, e->w[i].file, &e->w[i].width, &e->w[i].height)))
				err_exit(ERR_LOAD_TEXTURE);
			//printf("tex width: %d, height: %d\n", e->w[i].width, e->w[i].height);
			e->w[i].addr = mlx_get_data_addr(
					e->w[i].img, &e->w[i].bpp, &e->w[i].len, &e->w[i].endian);
			//log_img(e->w[i].addr, e->w[i].bpp, e->w[i].len, e->w[i].endian);
		}
		i++;
	}
	if (!(e->sprite.img = mlx_xpm_file_to_image(
				e->mlx, e->sprite.file, &e->sprite.width, &e->sprite.height)))
		err_exit(ERR_LOAD_SPRITE);
	//printf("tex width: %d, height: %d\n", e->sprite.width, e->sprite.height);
	e->sprite.addr = mlx_get_data_addr(
				e->sprite.img, &e->sprite.bpp, &e->sprite.len, &e->sprite.endian);
	//log_img(e->sprite.addr, e->sprite.bpp, e->sprite.len, e->sprite.endian);
}

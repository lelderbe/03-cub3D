/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils_p1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:39:50 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/04 21:11:01 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_pixel_put(t_img *img, double x, double y, int color)
{
	char	*dst;

	dst = img->addr + ((int)y * img->len + (int)x * (img->bpp / 8));
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
			e->w[i].addr = mlx_get_data_addr(
					e->w[i].img, &e->w[i].bpp, &e->w[i].len, &e->w[i].endian);
			log_img(&e->w[i]);
		}
		i++;
	}
	if (!(e->sprite.img = mlx_xpm_file_to_image(
				e->mlx, e->sprite.file, &e->sprite.width, &e->sprite.height)))
		err_exit(ERR_LOAD_SPRITE);
	e->sprite.addr = mlx_get_data_addr(
			e->sprite.img, &e->sprite.bpp, &e->sprite.len, &e->sprite.endian);
}

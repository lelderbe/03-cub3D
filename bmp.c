/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:06:56 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 11:32:44 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_bitmap_file_header(t_bmp *bmp, int fd)
{
	write(fd, &bmp->file.file_type, sizeof(bmp->file.file_type));
	write(fd, &bmp->file.file_size, sizeof(bmp->file.file_size));
	write(fd, &bmp->file.reserved1, sizeof(bmp->file.reserved1));
	write(fd, &bmp->file.reserved2, sizeof(bmp->file.reserved2));
	write(fd, &bmp->file.pixel_offset, sizeof(bmp->file.pixel_offset));
}

static void	print_bitmap_info_header(t_bmp *bmp, int fd)
{
	write(fd, &bmp->info, sizeof(bmp->info));
}

static void	print_img_data(t_img *img, int fd)
{
	int	y;

	y = img->height - 1;
	while (y >= 0)
	{
		write(fd, img->addr + y * img->len, img->len);
		y--;
	}
}

static void	init_bmp(t_bmp *bmp, t_img *img)
{
	ft_memset(bmp, 0, sizeof(*bmp));
	bmp->file.file_type = 0x4D42;
	bmp->file.file_size = 54 + img->len * img->height;
	bmp->file.pixel_offset = 54;
	bmp->info.header_size = 40;
	bmp->info.image_width = img->width;
	bmp->info.image_height = img->height;
	bmp->info.planes = 1;
	bmp->info.bpp = img->bpp;
}

void		save_img_to_bmp(t_img *img)
{
	t_bmp		bmp;
	int			fd;

	if ((fd = open(SAVE_FILENAME, O_WRONLY | O_CREAT, 0664)) < 0)
		err_exit(ERR_SAVE_BMP);
	init_bmp(&bmp, img);
	print_bitmap_file_header(&bmp, fd);
	print_bitmap_info_header(&bmp, fd);
	print_img_data(img, fd);
	close(fd);
}
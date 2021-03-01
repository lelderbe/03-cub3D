/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:12:15 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/01 15:24:10 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct		s_bmp {
	const unsigned short	file_type = 0x424D;
	unsigned		file_size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned		pixel_offset;

	unsigned		header_size;
	unsigned		image_width;
	unsigned		image_height;
	unsigned short	planes;
	unsigned short	bpp;
	unsigned		compression;
	unsigned		image_size;
	unsigned		x_pixels;
	unsigned		y_pixels;
	unsigned		total_colors;
	unsigned		important_colors;

}					t_bmp;

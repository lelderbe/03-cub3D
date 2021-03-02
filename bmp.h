/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:12:15 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 10:06:21 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

typedef struct			s_bmp {
	struct {
		unsigned short	file_type;
		unsigned		file_size;
		unsigned short	reserved1;
		unsigned short	reserved2;
		unsigned		pixel_offset;
	}					file;

	struct {
		unsigned		header_size;
		int				image_width;
		int				image_height;
		unsigned short	planes;
		unsigned short	bpp;
		unsigned		compression;
		unsigned		image_size;
		int				x_pixels;
		int				y_pixels;
		unsigned		total_colors;
		unsigned		important_colors;
	}					info;

}						t_bmp;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/02 16:22:05 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

# define APP_NAME "cub3D"
# define FAIL 0
# define OK 1

# define SAVE_OPTION "--save"
# define ERROR "Error"
# define ERROR_ARGS_COUNT "Invalid arguments count"

typedef struct	s_vars {
//	struct {
		char	*cub_filename;
		int		save_option;
//	}			args;

//	struct {
	unsigned	width;
	unsigned	height;
//	}			map;

//	struct {
	void		*mlx;
	void		*win;
//	}			mlx;

//	struct {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
//	}			img;
}				t_vars;

int				parse_params(int argc, char **argv, t_vars *e);
int				parse_cub_file(t_vars *e);

int				window_destroy_event(t_vars *e);
int				m_event(int button, int x, int y, t_vars *e);
int				motion_event(int x, int y, t_vars *e);
int				key_press_event(int keycode, t_vars *e);

#endif

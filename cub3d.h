/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/18 15:35:28 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

# define APP_NAME	"cub3D"
# define FAIL		0
# define OK			1

# define SAVE_OPTION		"--save"
# define ERROR				"Error"
# define ERROR_ARGS_COUNT	"Invalid arguments count"

# define TILE		64
# define SCALE		64
# define BODY		10
//# define STEP		SCALE / 8
# define STEP		1.0/8
# define LOOK_LEN	20
# define MAX_VIEW	1000

# define KEYCODE_ESC		53
# define KEYCODE_W			13
# define KEYCODE_A			0
# define KEYCODE_S			1
# define KEYCODE_D			2
# define KEYCODE_LEFT		123
# define KEYCODE_RIGHT		124

# define EV_KEY_PRESS		2
# define EV_MOTION_NOTIFY	6
# define EV_CREATE_NOTIFY	16
# define EV_DESTROY_NOTIFY	17

# define MASK_NO_EVENT			0L<<0
# define MASK_KEY_PRESS			1L<<0
# define MASK_POINTER_MOTION	1L<<6

# define FOV	60

# define CEIL_COLOR		0x00333333
# define FLOOR_COLOR	0x00666666
# define WALL_COLOR		0x00000066


typedef struct	s_vars {
//	struct {
	char		*cub_filename;
	int			save_option;
//	}			args;

//	struct {
	char		**map;
//	}			map;

//	struct {
	int			width;
	int			height;
	int			half_w;
	int			half_h;
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

//	struct {
//	int			pl_x;
//	int			pl_y;
	double		pl_x;
	double		pl_y;
	double		pl_ang;
	double		d;
//	}			pl;
}				t_vars;

int				parse_params(int argc, char **argv, t_vars *e);
int				parse_cub_file(t_vars *e);

int				event_window_create(t_vars *e);
int				event_window_destroy(t_vars *e);
int				event_m(int button, int x, int y, t_vars *e);
int				event_motion(int x, int y, t_vars *e);
int				event_key_press(int keycode, t_vars *e);

void			display_map(t_vars *e);
void			repaint(t_vars *e);

void			log_map(t_vars *e);
void			log_map2(t_vars *e);
void			log_pl(t_vars *e);

#endif

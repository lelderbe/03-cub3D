/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/23 16:03:46 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define APP_NAME			"cub3D"
# define FAIL				0
# define OK					1

# define SAVE_OPTION		"--save"
# define ERROR				"Error"
# define ERROR_ARGS_COUNT	"Invalid arguments count"
# define ERR_OPEN_FILE		"Can't open .cub file"
# define ERR_PARSE_FILE		"Error parse .cub file"
# define ERR_WRONG_RES		"Wrong resolution"
# define ERR_WRONG_TEXTURE	"Wrong texture option"
# define ERR_WRONG_COLOR	"Wrong color option"

# define PARSE_COMPL		8
# define R_RES				"R"
# define NO_NORTH			"NO"
# define SO_SOUTH			"SO"
# define WE_WEST			"WE"
# define EA_EAST			"EA"
# define F_COLOR			"F"
# define C_COLOR			"C"

# define MAP_TILE			20
# define MAP_BODY			10
# define TILE				150
# define SCALE				100
# define BODY				1.0 / 8
//# define STEP				SCALE / 8
# define STEP				1.0 / 8
# define ANGLE_STEP			10
# define LOOK_LEN			20
# define MAX_VIEW			10

# define WALL				'1'
# define EMPTY				'0'

# define KEYCODE_ESC		53
# define KEYCODE_W			13
# define KEYCODE_A			0
# define KEYCODE_S			1
# define KEYCODE_D			2
# define KEYCODE_LEFT		123
# define KEYCODE_RIGHT		124
# define KEYCODE_TAB		48

# define EV_KEY_PRESS		2
# define EV_KEY_RELEASE		3
# define EV_MOTION_NOTIFY	6
# define EV_CREATE_NOTIFY	16
# define EV_DESTROY_NOTIFY	17

# define MASK_NO_EVENT			0L<<0
# define MASK_KEY_PRESS			1L<<0
# define MASK_KEY_RELEASE		1L<<1
# define MASK_POINTER_MOTION	1L<<6

# define FOV		60
# define HALF_FOV	FOV / 2

# define CEIL_COLOR		0x00333333
# define FLOOR_COLOR	0x00666666
# define WALL_COLOR		0x00000066


typedef struct	s_wall {
	char		*file;
	void		*img;
	int			width;
	int			height;
	void		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_wall;

typedef struct	s_vars {
//	struct {
	char		*cub_filename;
	int			fd;
	int			save_option;
//	}			args;

//	struct {
	char		**map;
	int			visible;
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
	int			wall_color;
	unsigned	floor_color;
	unsigned	ceil_color;
//	}			opts;

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
	int			pl_a;
	int			pl_w;
	int			pl_s;
	int			pl_d;
	int			pl_left;
	int			pl_right;
//	}			pl;

	int			color;

//	struct {
//	}			textures;

	t_wall		w[4];
	//t_wall		wn;
	//t_wall		ws;
	//t_wall		we;
	//t_wall		ww;

//	struct {
	double		wall_x;
//	}			textures;

	int			parsed;
}				t_vars;

int				parse_params(int argc, char **argv, t_vars *e);
int				parse_cub_file(t_vars *e);

void			texture_load(t_vars *e);

int				event_window_create(t_vars *e);
int				event_window_destroy(t_vars *e);
int				event_m(int button, int x, int y, t_vars *e);
int				event_motion(int x, int y, t_vars *e);
int				event_key_press(int keycode, t_vars *e);
int				event_key_release(int keycode, t_vars *e);
void			pl_check_and_move(t_vars *e, double dx, double dy);

void			display_map(t_vars *e);
int				repaint(t_vars *e);

void			log_map(t_vars *e);
void			log_map2(t_vars *e);
void			log_pl(t_vars *e);
void			log_img(void *addr, int bpp, int len, int endian);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/10 13:51:13 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "bmp.h"
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

# define USE_MANY_COLORS	1
# define USE_TEXTURES		1
# define USE_FOG			0
# define WALL_COLLISION		0
# define MOUSE_ON			0

# define APP_NAME			"cub3D"
# define FAIL				0
# define OK					1

# define ___ERRORS___		"All errors are here"
# define SAVE_OPTION		"--save"
# define SAVE_FILENAME		"screenshot.bmp"
# define ERROR				"Error"
# define ERR_NO_CUB_FILE	"No .cub file given"
# define ERR_ARGS_COUNT		"Wrong arguments count"
# define ERR_INVALID_ARG	"Wrong second argument"
# define ERR_OPEN_FILE		"Can't open .cub file"
# define ERR_PARSE_FILE		"Error parse .cub file"
# define ERR_DUPLICATE_OPT	"Duplicate option"
# define ERR_WRONG_RES		"Wrong resolution option"
# define ERR_WRONG_TEXTURE	"Wrong texture option"
# define ERR_WRONG_COLOR	"Wrong color option"
# define ERR_OUT_OF_MEM		"Not enough memory"
# define ERR_INVALID_MAP	"Invalid map data"
# define ERR_MLX_INIT		"Error mlx init"
# define ERR_MLX_WINDOW		"Error window create"
# define ERR_LOAD_TEXTURE	"Error load texture from file"
# define ERR_LOAD_SPRITE	"Error load sprite from file"
# define ERR_SAVE_BMP		"Error save bmp file"

# define ___OPTIONS___		".cub file options"
# define R_RES				"R"
# define NO_NORTH			"NO"
# define SO_SOUTH			"SO"
# define WE_WEST			"WE"
# define EA_EAST			"EA"
# define S_SPRITE			"S"
# define F_COLOR			"F"
# define C_COLOR			"C"

# define ___MAP_SYMBOLS___	"all allowed map symbols, grouped by types"
# define MAP_ALLOWED_CHARS	" 012ENWS"
# define MAP_WALL			'1'
# define MAP_EMPTY			'0'
# define PL_ALLOWED_CHARS	"ENWS"
# define SPRITE_SYMBOLS		"2"

# define ___PARSE___		"parse options, set bit when option is parsed"
# define PARSE_OPT_COMPLETE	255
# define R_BIT				1
# define NO_BIT				1<<1
# define SO_BIT				1<<2
# define WE_BIT				1<<3
# define EA_BIT				1<<4
# define S_BIT				1<<5
# define F_BIT				1<<6
# define C_BIT				1<<7

# define ___2D_DEFAULTS___	"2D mini-map defaults"
# define MAP_TILE			20
# define MAP_COLOR			0x00999999
# define MAP_PL_BODY		20 * BODY
# define MAP_PL_BODY_COLOR	0x0000FF00
# define MAP_RAY_COLOR		0x000000FF
# define MAP_RAY_STEP		0.05
# define MAP_RAYS_SHOW		1

# define ___3D_DEFAULTS___	"3D defaults"
# define BODY				1.0 / 2
# define STEP				1.0 / 8
# define ANGLE_STEP			5
# define FOV				60
# define MAX_VIEW			200

# define ___COLOR_DEFS___	"default color values"
# define DEF_CEIL_COLOR		0x00333333
# define DEF_FLOOR_COLOR	0x00666666
# define DEF_WALL_COLOR		0x00000066
# define TRANSPARENT_COLOR	0x00980088

# define ___WALL_SIDE___	"index of walls side"
# define E_WALL				0
# define N_WALL				1
# define W_WALL				2
# define S_WALL				3

# define ___KEYCODES___		"keys and their keycodes"
# define KEYCODE_ESC		53
# define KEYCODE_W			13
# define KEYCODE_A			0
# define KEYCODE_S			1
# define KEYCODE_D			2
# define KEYCODE_LEFT		123
# define KEYCODE_RIGHT		124
# define KEYCODE_TAB		48

# define ___EVENTS___		"events and masks for hooks"
# define EV_KEY_PRESS		2
# define EV_KEY_RELEASE		3
# define EV_MOTION_NOTIFY	6
# define EV_DESTR_NOTIFY	17

# define MASK_NO_EVENT		0L<<0
# define MASK_KEY_PRESS		1L<<0
# define MASK_KEY_RELEASE	1L<<1
# define MASK_PTR_MOTION	1L<<6

typedef struct	s_img {
	char		*file;
	void		*img;
	int			w;
	int			h;
	int			half_w;
	int			half_h;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_img;

typedef struct	s_spr {
	double		x;
	double		y;
	double		d;
	double		ang;
}				t_spr;

typedef struct	s_cub {
	char		*cub_filename;
	int			cub_fd;
	int			save_option;
	int			sys_width;
	int			sys_height;
	int			map_parse_started;
	char		parsed;

	void		*mlx;
	void		*win;
	int			width;
	int			height;

	t_img		main;
	t_img		mp;
	t_img		w[4];
	t_img		sprite;

	t_list		*map_lst;
	char		**map;
	unsigned	map_w;
	unsigned	map_h;
	int			map_visible;

	unsigned	w_clr;
	unsigned	f_clr;
	unsigned	c_clr;

	double		pl_x;
	double		pl_y;
	double		pl_a;
	int			pl_key_a;
	int			pl_key_w;
	int			pl_key_s;
	int			pl_key_d;
	int			pl_key_left;
	int			pl_key_right;

	int			color;
	int			hcolor;
	int			vcolor;

	double		dpp;
	double		hit;
	double		hit_x;
	double		hit_y;
	int			side;
	int			side_h;
	int			side_v;
	int			wall;
	int			wall_h;
	int			wall_v;

	double		*atans;
	double		*z;
	t_spr		**s;
	int			s_count;

	int			s_h;
	int			s_w;
	double		s_dx;
	double		s_dy;
	double		s_st_x;
	double		s_st_y;
	int			s_c;

	int			t_h;
	int			t_w;
	double		t_st;
	int			y_ceil;
	int			y_floor;

	int			of;

	int			m_x;
	int			m_y;

}				t_cub;

void			parse_arguments(int argc, char **argv, t_cub *e);
void			parse_cub_file(t_cub *e);
int				parse_line(t_cub *e, char *line);
void			parse_map(t_cub *e);
void			parse_sprites(t_cub *e);
int				check_atoi(char *s, int min, int max);

int				ev_window_destroy();
int				ev_key_press(int keycode, t_cub *e);
int				ev_key_release(int keycode, t_cub *e);
int				ev_mouse_motion(int x, int y, t_cub *e);

void			render(t_cub *e);
int				repaint(t_cub *e);

int				eq(char *s1, char *s2);
int				exit_cub(t_cub *e, char *err);
void			free_split(char **s);
double			cos_a(double ang);
double			sin_a(double ang);
void			free_resources(t_cub *e);
int				cub_atoi(const char *str);

int				create_trgb(int t, int r, int g, int b);
int				add_shade(double d, unsigned color);
void			img_pixel_put(t_img *img, double x, double y, int color);
int				get_color_sp(t_cub *e, int dx, int dy);
void			textures_load(t_cub *e);

void			clear_2d_map_window(t_cub *e);
void			display_2d_map(t_cub *e);
void			display_2d_ray(t_cub *e, double ray_ang, double ray_d);
void			display_2d_sprites(int x, int y, t_cub *e);
void			display_3d_column(t_cub *e, int column, double d);
void			display_3d_sprites(t_cub *e);

void			save_img_to_bmp(t_cub *e, t_img *img, int of);

#endif

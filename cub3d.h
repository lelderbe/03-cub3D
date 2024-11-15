/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/13 09:35:56 by lelderbe         ###   ########.fr       */
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

// # define USE_FOG			0
# define WALL_COLLISION		1
# define MOUSE_ON			0
# define USE_SPRITES		1

# define APP_NAME			"cub3D"
# define FAIL				0
# define OK					1

# define SAVE_OPTION		"--save"
# define SAVE_FILENAME		"screenshot.bmp"

/**
 * ERRORS - All errors are here
 */
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

/**
 * OPTIONS - .cub file options
 */
# define R_RES				"R"
# define NO_NORTH			"NO"
# define SO_SOUTH			"SO"
# define WE_WEST			"WE"
# define EA_EAST			"EA"
# define S_SPRITE			"S"
# define F_COLOR			"F"
# define C_COLOR			"C"

/**
 * MAP_SYMBOLS - all allowed map symbols, grouped by types
 * 
 */
# define MAP_ALLOWED_CHARS	" 012ENWS"
# define MAP_WALL			'1'
# define MAP_EMPTY			'0'
# define PL_ALLOWED_CHARS	"ENWS"
# define SPRITE_SYMBOLS		"2"

/**
 * PARSE - parse options, set bit when option is parsed
 */
# define PARSE_OPT_COMPLETE	255
# define R_BIT				1<<0
# define NO_BIT				1<<1
# define SO_BIT				1<<2
# define WE_BIT				1<<3
# define EA_BIT				1<<4
# define S_BIT				1<<5
# define F_BIT				1<<6
# define C_BIT				1<<7

/**
 * 2D_DEFAULTS - mini map defaults
 */
# define MAP_TILE			20			// cell size
# define MAP_COLOR			0x00999999
# define MAP_PL_BODY		20 * BODY
# define MAP_PL_BODY_COLOR	0x0000FF00
# define MAP_RAY_COLOR		0x000000FF
# define MAP_RAY_STEP		0.05		// smaller - better, but slower
# define MAP_RAYS_SHOW		1			// show FOV rays

/**
 * 3D_DEFAULTS
 */
# define BODY				1.0 / 2		// player's body size
# define STEP				1.0 / 8		// one step value
# define ANGLE_STEP			5			// turn by this value degreeds
# define FOV				60			// player's FOV
# define MAX_VIEW			200			// max distance to render

# define USE_ONE_COLOR		1<<0		// use one color for walls
# define USE_MANY_COLORS	1<<1		// use many colors
# define USE_TEXTURES		1<<2		// use textures for walls

/**
 * COLORS DEFAULTS
 */
# define DEF_CEIL_COLOR		0x00333333
# define DEF_FLOOR_COLOR	0x00666666
# define DEF_WALL_COLOR		0x00000066
# define TRANSPARENT_COLOR	0x00980088

/**
 * WALL_SIDES
 */
# define E_WALL				0
# define N_WALL				1
# define W_WALL				2
# define S_WALL				3

/**
 * KEYCODES - keys and their keycodes
 */
# define KEYCODE_ESC		53
# define KEYCODE_W			13
# define KEYCODE_A			0
# define KEYCODE_S			1
# define KEYCODE_D			2
# define KEYCODE_LEFT		123
# define KEYCODE_RIGHT		124
# define KEYCODE_TAB		48
# define KEYCODE_1			18
# define KEYCODE_2			19
# define KEYCODE_3			20
# define KEYCODE_4			21
# define KEYCODE_5			23

/**
 * EVENTS - events and masks for hooks
 */
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

	t_img		main;		// main image
	t_img		mp;			// minimap image
	t_img		w[4];		// walls textures
	t_img		sprite;		// sprite texture

	t_list		*map_lst;	// load minimap in list
	char		**map;		// convert minimap in array
	unsigned	map_w;		// width of map
	unsigned	map_h;		// height of map
	int			map_visible;	// show minimap

	unsigned	w_clr;		// wall color
	unsigned	f_clr;		// floor color
	unsigned	c_clr;		// ceil color

	double		pl_x;		// player x
	double		pl_y;		// player y
	double		pl_a;		// player angle
	int			pl_key_a;	// pressed keys
	int			pl_key_w;
	int			pl_key_s;
	int			pl_key_d;
	int			pl_key_left;
	int			pl_key_right;

	int			color;
	int			hcolor;
	int			vcolor;

	// render walls
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

	double		*atans;		// for walls correction - calculated angles for rays
	double		*z;			// z-buffer
	t_spr		**s;		// sprites array
	int			s_count;

	// sprite render
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

	int			of;			// offset of sprites image

	int			m_x;		// mouse x
	int			m_y;		// mouse y

	int			walls_style;	// hotkeys: 1 2 3
	int			use_sprites;	// hotkey: 4
	int			wall_collision;	// hotkey: 5
}				t_cub;

void			parse_arguments(int argc, char **argv, t_cub *e);
void			parse_cub_file(t_cub *e);
int				parse_line(t_cub *e, char *line);
void			parse_map(t_cub *e);
void			parse_sprites(t_cub *e);
int				check_atoi(char *s, int min, int max);

int				ev_window_destroy(t_cub *e);
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

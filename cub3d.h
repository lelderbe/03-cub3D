/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/04 13:24:55 by lelderbe         ###   ########.fr       */
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

# define USE_MANY_COLORS	1
# define USE_TEXTURES		1
# define USE_FOG			0

# define APP_NAME			"cub3D"
# define FAIL				0
# define OK					1

# define SAVE_OPTION		"--save"
# define SAVE_FILENAME		"screenshot.bmp"
# define ERROR				"Error"
# define ERR_ARGS_COUNT		"Invalid arguments count"
# define ERR_INVALID_ARG	"Invalid argument"
# define ERR_OPEN_FILE		"Can't open .cub file"
# define ERR_PARSE_FILE		"Error parse .cub file"
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

# define R_RES				"R"
# define NO_NORTH			"NO"
# define SO_SOUTH			"SO"
# define WE_WEST			"WE"
# define EA_EAST			"EA"
# define S_SPRITE			"S"
# define F_COLOR			"F"
# define C_COLOR			"C"

# define MAP_ALLOWED_CHARS	" 012ENWS"
# define MAP_WALL			'1'
# define MAP_EMPTY			'0'
# define PL_ALLOWED_CHARS	"ENWS"

# define PARSE_OPT_COMPLETE	255
//# define PARSE_CHECK		0
# define R_BIT				1
# define NO_BIT				1<<1
# define SO_BIT				1<<2
# define WE_BIT				1<<3
# define EA_BIT				1<<4
# define S_BIT				1<<5
# define F_BIT				1<<6
# define C_BIT				1<<7

# define MAP_TILE			20
# define MAP_COLOR			0x00999999
# define MAP_PL_BODY		20 * BODY
# define MAP_PL_BODY_COLOR	0x0000FF00
# define MAP_RAY_COLOR		0x000000FF
# define MAP_RAY_STEP		0.01
# define MAP_RAYS_SHOW		1
# define TILE				100
//# define SCALE				100
# define BODY				1.0 / 2
# define STEP				1.0 / 8
# define ANGLE_STEP			5
//# define MAP_RAY_COLOR		0x0000FF00
# define FOV				60
# define HALF_FOV			FOV / 2

# define E_WALL				0
# define N_WALL				1
# define W_WALL				2
# define S_WALL				3

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
# define EV_DESTR_NOTIFY	17

# define MASK_NO_EVENT		0L<<0
# define MASK_KEY_PRESS		1L<<0
# define MASK_KEY_RELEASE	1L<<1
# define MASK_PTR_MOTION	1L<<6

# define DEF_CEIL_COLOR		0x00333333
# define DEF_FLOOR_COLOR	0x00666666
# define DEF_WALL_COLOR		0x00000066
# define TRANSPARENT_COLOR	0x00980088

typedef struct	s_img {
	char		*file;
	void		*img;
	int			width;
	int			height;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_img;

typedef struct	s_spr {
	double		x;
	double		y;

}				t_spr;

typedef struct	s_cub {
//	struct {
	char		*cub_filename;
	int			fd;
	int			save_option;
	int			sys_width;
	int			sys_height;
//	}			args;

//	struct {
	char		parsed;
	int			map_parse_started;
	int			pl_count;
//	}			parser;

//	struct {
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			half_w;
	int			half_h;
//	}			mlx;

	t_img		main;
	t_img		mp;

//	struct {
	t_list		*map_lst;	
	char		**map;
	unsigned	map_width;
	unsigned	map_height;
	int			map_visible;
//	}			map;

//	struct {
	int			wall_color;
	unsigned	floor_color;
	unsigned	ceil_color;
//	}			defaults;

//	struct {
	double		pl_x;
	double		pl_y;
	double		pl_a;
	int			pl_key_a;
	int			pl_key_w;
	int			pl_key_s;
	int			pl_key_d;
	int			pl_key_left;
	int			pl_key_right;
//	}			pl;

	int			color;
	int			hcolor;
	int			vcolor;

//	struct {
	t_img		w[4];
	t_img		sprite;
//	}			textures;

	double		dpp;
//	struct {
	double		hit;
	double		hit_x;
	double		hit_y;
	int			side;
	int			side_h;
	int			side_v;
//	}			rays;

	int			mouse_x;
	int			mouse_y;

	double		*atans;
	double		*z;
	t_spr		**s;

}				t_cub;

void			parse_arguments(int argc, char **argv, t_cub *e);
void			parse_cub_file(t_cub *e);
int				parse_line(t_cub *e, char *line);
void			parse_map(t_cub *e);

//int				ev_window_create();
int				ev_window_destroy();
int				ev_m(int button, int x, int y, t_cub *e);
int				ev_mouse_motion(int x, int y, t_cub *e);
int				ev_key_press(int keycode, t_cub *e);
int				ev_key_release(int keycode, t_cub *e);

void			pl_move(t_cub *e, double dx, double dy);
void			render(t_cub *e);
int				repaint(t_cub *e);

int				eq(char *s1, char *s2);
int				err_exit(char *err);
void			free_split(char **s);
double			cos_a(double ang);
double			sin_a(double ang);

int				create_trgb(int t, int r, int g, int b);
int				add_shade(double d, unsigned color);
void			img_pixel_put(t_img *img, double x, double y, int color);
void			textures_load(t_cub *e);

void			clear_2d_map_window(t_cub *e);
void			display_2d_map(t_cub *e);
void			display_2d_ray(t_cub *e, double ray_ang, double ray_d);
void			display_3d_floor_ceil(t_cub *e);
void			display_3d_column(t_cub *e, int column, double d);
void			display_3d_column_v2(t_cub *e, int column, double d);
void			draw_sprites(t_cub *e);

void			log_map(char **map);
void			log_map2(char **map);
void			log_pl(t_cub *e);
void			log_img(t_img *img);
void			log_lst(t_list *lst);
void			log_eq(char *s1, char *s2);
void			log_bmp(t_bmp *bmp);
void			log_sprites(t_spr **s);

void			save_img_to_bmp(t_img *img);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/26 14:32:57 by lelderbe         ###   ########.fr       */
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
# define ERR_WRONG_RES		"Wrong resolution option"
# define ERR_WRONG_TEXTURE	"Wrong texture option"
# define ERR_WRONG_COLOR	"Wrong color option"
# define ERR_OUT_OF_MEM		"Not enough memory"
# define ERR_INVALID_MAP	"Invalid map data"

# define R_RES				"R"
# define NO_NORTH			"NO"
# define SO_SOUTH			"SO"
# define WE_WEST			"WE"
# define EA_EAST			"EA"
# define S_SPRITE			"S"
# define F_COLOR			"F"
# define C_COLOR			"C"

# define MAP_ALLOWED_CHARS	" 012ENWS"
# define PL_ALLOWED_CHARS	"ENWS"

# define PARSE_COMPLETE		255
# define R_BIT				1
# define NO_BIT				1<<1
# define SO_BIT				1<<2
# define WE_BIT				1<<3
# define EA_BIT				1<<4
# define S_BIT				1<<5
# define F_BIT				1<<6
# define C_BIT				1<<7

# define MAP_TILE			20
# define MAP_BODY			10
# define TILE				100
//# define SCALE				100
# define BODY				1.0 / 8
//# define STEP				SCALE / 8
# define STEP				1.0 / 8
# define ANGLE_STEP			10
//# define LOOK_LEN			30
# define MAX_VIEW			20

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


typedef struct	s_tex {
	char		*file;
	void		*img;
	int			width;
	int			height;
	void		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_tex;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_img;

typedef struct	s_vars {
//	struct {
	char		*cub_filename;
	int			fd;
	int			save_option;
//	}			args;

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
	char		**map;
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
	double		pl_ang;
	int			pl_a;
	int			pl_w;
	int			pl_s;
	int			pl_d;
	int			pl_left;
	int			pl_right;
//	}			pl;

	int			color;

//	struct {
	t_tex		w[4];
	t_tex		sprite;
	double		wall_x;
//	}			textures;

//	struct {
	double		d;
	double		hit_x;
	double		hit_y;
	int			hit;
	int			vhit;
	int			hhit;
//	}			rays;

//	struct {
	t_list		*map_lst;	
	char		parsed;
	int			map_parse_started;
	size_t		map_max;
	int			map_lines;
	int			pl_count;
//	}			parser;
}				t_vars;

int				parse_params(int argc, char **argv, t_vars *e);
int				parse_cub_file(t_vars *e);
int				parse_map_line(t_vars *e, char *line);
//void			parse_pl_pos(t_vars *e, const char *pl_allowed_chars);
void			parse_map(t_vars *e);

void			texture_load(t_vars *e);

int				event_window_create(t_vars *e);
int				event_window_destroy(t_vars *e);
int				event_m(int button, int x, int y, t_vars *e);
int				event_motion(int x, int y, t_vars *e);
int				event_key_press(int keycode, t_vars *e);
int				event_key_release(int keycode, t_vars *e);
void			pl_check_and_move(t_vars *e, double dx, double dy);

int				repaint(t_vars *e);

int				eq(char *s1, char *s2);
int				err_exit(char *err);
void			free_split(char **s);

int				create_trgb(int t, int r, int g, int b);
void			img_pixel_put(t_img *img, double x, double y, int color);

void			clear_2d_map_window(t_vars *e);
void			display_2d_map(t_vars *e);
//void			display_2d_wall_box(int x, int y, t_vars *e);
//void			display_2d_pl(t_vars *e);
//void			display_2d_look_line(t_vars *e);

void			log_map(t_vars *e);
void			log_map2(t_vars *e);
void			log_pl(t_vars *e);
void			log_img(void *addr, int bpp, int len, int endian);
void			log_lst(t_list *lst);
void			log_eq(char *s1, char *s2);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:16:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/03 13:25:13 by lelderbe         ###   ########.fr       */
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

# define SCALE	64 
# define BODY	10
# define STEP	8

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
	int			pl_x;
	int			pl_y;
	double		pl_ang;
//	}			pl;
}				t_vars;

int				parse_params(int argc, char **argv, t_vars *e);
int				parse_cub_file(t_vars *e);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:46:54 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/24 19:35:32 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		err_exit(char *err)
{
		ft_putendl_fd(ERROR, 1);
		ft_putendl_fd(err, 1);
		exit (1);
}

int		parse_params(int argc, char **argv, t_vars *e)
{
	(void)argv;

	if (argc < 2 || argc > 3)	//error
		err_exit(ERROR_ARGS_COUNT);
	e->cub_filename = argv[1];
	e->fd = open(e->cub_filename, O_RDONLY);
	if (e->fd == -1)	//error
		err_exit(ERR_OPEN_FILE);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], SAVE_OPTION, 10) == 0)
		{
			e->save_option = 1;
			printf("save_option = 1\n");
		}
		else
		{
			//error argument
			printf("wrong second option\n");
			return (FAIL);
		}
	}
	return (OK);
}

static int	parse_r(t_vars *e, char **parts)
{
	if (parts[1] != 0 && parts[2] != 0)
	{
		// TODO: if > MAX then = MAX
		e->width = ft_atoi(parts[1]);
		e->height = ft_atoi(parts[2]);
		if (!(e->width <= 0 || e->height <= 0))
			return (OK);
	}
	return err_exit(ERR_WRONG_RES);
}

static int	parse_texture(t_tex *tex, char **parts)
{
	if (parts[1] != 0)
	{
		tex->file = ft_strdup(parts[1]);
		return (OK);
	}
	return err_exit(ERR_WRONG_TEXTURE);
}

static int	parse_color(unsigned int *value, char **parts)
{
	char	**rgb;

	// TODO: free split
	if (parts[1] != 0)
	{
		if (!(rgb = ft_split(parts[1], ',')))
			return err_exit(ERR_OUT_OF_MEM);
		if (rgb[0] != 0 && rgb[1] != 0 && rgb[2] != 0)
		{
			*value = (ft_atoi(rgb[0]) << 16) +
					(ft_atoi(rgb[1]) << 8) +
					(ft_atoi(rgb[2]));
			return (OK);
		}
	}
	return err_exit(ERR_WRONG_COLOR);
}

int		eq(char *s1, char *s2)
{
	int	len;

	if (!s1 || !s2)
		return (FAIL);
	len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
	if (ft_strncmp(s1, s2, len) == 0)
		return (OK);
	return (FAIL);
}

int		parse_map(t_vars *e, char *line)
{
	// TODO wrong symbols -> error
	// TODO empty -> error
	// TODO more one pl -> error
	(void)e;
	(void)line;
	if (ft_strlen(line) == 0)
		return (FAIL);
	ft_lstadd_back(&e->lst, ft_lstnew(line));
	return (OK);
}

int		parse_line(t_vars *e, char *line)
{
	char	**parts;

	if (!(parts = ft_split(line, ' ')))
		err_exit(ERR_OUT_OF_MEM);
	if (parts[0] != 0)
	{
		if (parts[0] && eq(parts[0], R_RES) && parse_r(e, parts))
			e->parsed |= R_BIT;
		else if (parts[0] && eq(parts[0], S_SPRITE) && parse_texture(&e->sprite, parts))
			e->parsed |= S_BIT;
		else if (parts[0] && eq(parts[0], F_COLOR) && parse_color(&e->floor_color, parts))
			e->parsed |= F_BIT;
		else if (parts[0] && eq(parts[0], C_COLOR) && parse_color(&e->ceil_color, parts))
			e->parsed |= C_BIT;
		else if (parts[0] && eq(parts[0], EA_EAST) && parse_texture(&e->w[0], parts))
			e->parsed |= EA_BIT;
		else if (parts[0] && eq(parts[0], NO_NORTH) && parse_texture(&e->w[1], parts))
			e->parsed |= NO_BIT;
		else if (parts[0] && eq(parts[0], WE_WEST) && parse_texture(&e->w[2], parts))
			e->parsed |= WE_BIT;
		else if (parts[0] && eq(parts[0], SO_SOUTH) && parse_texture(&e->w[3], parts))
			e->parsed |= SO_BIT;
		else // sould be a MAP
			parse_map(e, line);
	}
	// TODO: free split
	return (OK);
}

void	parse_pl_pos(t_vars *e)
{
	int			x;
	int			y;
	int			count;
	char		*ptr;
	const char	*pos = "ENWS";

	count = 0;
	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if ((ptr = ft_strchr(pos, e->map[y][x])) != 0)
			{
				e->pl_x = x + 0.5;
				e->pl_y = y + 0.5;
				e->pl_ang = (ptr - pos) * 90;
				//e->pl_ang = e->map[y][x] == 'S' ? 270 : e->pl_ang;
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		err_exit(ERR_INVALID_MAP);
}

int		parse_cub_file(t_vars *e)
{
	char	**map;
	char	*line;
	int		result;
	
	while ((result = get_next_line(e->fd, &line)))
	{
		if (parse_line(e, line) == FAIL)
		{
			return (FAIL);
		}
		//printf("%s\n", line);
		//printf("%u\n", (unsigned char)e->parsed);
	}
	if ((unsigned char)e->parsed != PARSE_COMPL)
		err_exit(ERR_PARSE_FILE);
	log_lst(e->lst);
	map = malloc(sizeof(*map) * (6 + 1));
	map[0] = ft_strdup("1111111110");
	map[1] = ft_strdup("1000000011");
	map[2] = ft_strdup("1000110011");
	map[3] = ft_strdup("1000010011");
	map[4] = ft_strdup("1N00000001");
	map[5] = ft_strdup("1111111111");
	map[6] = 0;
	printf("e->width: %d, e->height: %d\n", e->width, e->height);
	e->half_w = e->width / 2;
	e->half_h = e->height / 2;
	e->d = 1.0 * e->half_w / tan((FOV / 2) * M_PI / 180) / 1;
	//e->d = (1.0 * e->half_w / TILE) / tan((FOV / 2) * M_PI / 180);
	printf("e->d: %6.2f\n", e->d);

	e->map = map;
	e->visible = 1;
	parse_pl_pos(e);
	//e->pl_x = 1 * SCALE + SCALE / 2;
	//e->pl_y = 2 * SCALE + SCALE / 2;
	//e->pl_x = 1 + 0.5;
	//e->pl_y = 4 + 0.5;
	//e->pl_ang = 90;
	return (OK);
}

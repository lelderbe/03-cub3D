/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:46:54 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/27 20:37:51 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_params(int argc, char **argv, t_vars *e)
{
	if (argc < 2 || argc > 3)
		err_exit(ERR_ARGS_COUNT);
	e->cub_filename = argv[1];
	e->fd = open(e->cub_filename, O_RDONLY);
	if (e->fd == -1)
		err_exit(ERR_OPEN_FILE);
	if (argc == 3)
	{
		if (eq(argv[2], SAVE_OPTION))
			e->save_option = 1;
		else
			err_exit(ERR_INVALID_ARG);
	}
	return (OK);
}

static int	parse_r(t_vars *e, char **parts)
{
	if (e->map_parse_started)
		return err_exit(ERR_PARSE_FILE);
	if (parts[1] && parts[2] && !parts[3])
	{
		// TODO: if > MAX then = MAX
		e->width = ft_atoi(parts[1]);
		e->height = ft_atoi(parts[2]);
		if (!(e->width <= 0 || e->height <= 0))
			return (OK);
	}
	return err_exit(ERR_WRONG_RES);
}

static int	parse_texture(t_vars *e, t_tex *tex, char **parts)
{
	if (e->map_parse_started)
		return err_exit(ERR_PARSE_FILE);
	if (parts[1] && !parts[2])
	{
		if (!(tex->file = ft_strdup(parts[1])))
			return err_exit(ERR_OUT_OF_MEM);
		return (OK);
	}
	return err_exit(ERR_WRONG_TEXTURE);
}

static int	parse_color(t_vars *e, unsigned int *value, char **parts)
{
	char	**rgb;

	if (e->map_parse_started)
		return err_exit(ERR_PARSE_FILE);
	if (parts[1] != 0)
	{
		if (!(rgb = ft_split(parts[1], ',')))
			return err_exit(ERR_OUT_OF_MEM);
		if (rgb[0] && rgb[1] && rgb[2] && !rgb[3])
		{
			*value = create_trgb(0,
				ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
			free_split(rgb);
			return (OK);
		}
	}
	return err_exit(ERR_WRONG_COLOR);
}

static int	parse_line(t_vars *e, char *line)
{
	char	**parts;

	if (!(parts = ft_split(line, ' ')))
		return err_exit(ERR_OUT_OF_MEM);
	if (eq(parts[0], R_RES) && parse_r(e, parts))
		e->parsed |= R_BIT;
	else if (eq(parts[0], S_SPRITE) && parse_texture(e, &e->sprite, parts))
		e->parsed |= S_BIT;
	else if (eq(parts[0], F_COLOR) && parse_color(e, &e->floor_color, parts))
		e->parsed |= F_BIT;
	else if (eq(parts[0], C_COLOR) && parse_color(e, &e->ceil_color, parts))
		e->parsed |= C_BIT;
	else if (eq(parts[0], EA_EAST) && parse_texture(e, &e->w[0], parts))
		e->parsed |= EA_BIT;
	else if (eq(parts[0], NO_NORTH) && parse_texture(e, &e->w[1], parts))
		e->parsed |= NO_BIT;
	else if (eq(parts[0], WE_WEST) && parse_texture(e, &e->w[2], parts))
		e->parsed |= WE_BIT;
	else if (eq(parts[0], SO_SOUTH) && parse_texture(e, &e->w[3], parts))
		e->parsed |= SO_BIT;
	else
		parse_map_line(e, line);
	free_split(parts);
	return (OK);
}

int		parse_cub_file(t_vars *e)
{
	char	*line;
	int		result;
	
	while ((result = get_next_line(e->fd, &line)))
	{
		parse_line(e, line);
		free(line);
	}
	if (ft_strlen(line) > 0)
		parse_line(e, line);
	free(line);
	if ((unsigned char)e->parsed != PARSE_OPT_COMPLETE)
		err_exit(ERR_PARSE_FILE);
	parse_map(e);
	printf("e->width: %d, e->height: %d\n", e->width, e->height);
	e->half_w = e->width / 2;
	e->half_h = e->height / 2;
	e->dpp = 1.0 * e->half_w / tan((FOV / 2) * M_PI / 180) / 1;
	//e->d = (1.0 * e->half_w / TILE) / tan((FOV / 2) * M_PI / 180);
	printf("e->dpp: %6.2f\n", e->dpp);
	e->map_visible = 0;
	return (OK);
}

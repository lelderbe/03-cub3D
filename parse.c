/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:46:54 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/23 16:26:15 by lelderbe         ###   ########.fr       */
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

static int	parse_resolution(t_vars *e, char **parts)
{
	int value;

	if (parts[1] != 0 && parts[2] != 0)
	{
		value = ft_atoi(parts[1]);
		if (value <= 0)
			return (FAIL);
		e->width = value;
		value = ft_atoi(parts[2]);
		if (value <= 0)
		 	 return (FAIL);
		e->height = value;
		return (OK);
	}
	return (FAIL);
}

static int	parse_texture(t_vars *e, char **parts, int index)
{
	if (parts[1] != 0)
	{
		e->w[index].file = ft_strdup(parts[1]);
		return (OK);
	}
	return (FAIL);
}

static int	parse_color(unsigned int *value, char **parts)
{
	char	**rgb;

	// TODO: free split
	if (parts[1] != 0)
	{
		if (!(rgb = ft_split(parts[1], ',')))
			return (FAIL);
		if (rgb[0] != 0 && rgb[1] != 0 && rgb[2] != 0)
		{
			*value = (ft_atoi(rgb[0]) << 16) +
					(ft_atoi(rgb[1]) << 8) +
					(ft_atoi(rgb[2]));
			return (OK);
		}
	}
	return (FAIL);
}

int		parse_line(t_vars *e, char *line)
{
	char	**parts;
	//int		i;

	if (!(parts = ft_split(line, ' ')))
		err_exit(ERR_PARSE_FILE);
	if (parts[0] != 0)
	{
		if (ft_strncmp(parts[0], R_RES, ft_strlen(parts[0])) == 0)
			if (parse_resolution(e, parts) == FAIL)
				err_exit(ERR_WRONG_RES);
		if (ft_strncmp(parts[0], EA_EAST, ft_strlen(parts[0])) == 0)
			if (parse_texture(e, parts, 0) == FAIL)
				err_exit(ERR_WRONG_TEXTURE);
		if (ft_strncmp(parts[0], NO_NORTH, ft_strlen(parts[0])) == 0)
			if (parse_texture(e, parts, 1) == FAIL)
				err_exit(ERR_WRONG_TEXTURE);
		if (ft_strncmp(parts[0], WE_WEST, ft_strlen(parts[0])) == 0)
			if (parse_texture(e, parts, 2) == FAIL)
				err_exit(ERR_WRONG_TEXTURE);
		if (ft_strncmp(parts[0], SO_SOUTH, ft_strlen(parts[0])) == 0)
			if (parse_texture(e, parts, 3) == FAIL)
				err_exit(ERR_WRONG_TEXTURE);
		if (ft_strncmp(parts[0], F_COLOR, ft_strlen(parts[0])) == 0)
			if (parse_color(&e->floor_color, parts) == FAIL)
				err_exit(ERR_WRONG_COLOR);
		if (ft_strncmp(parts[0], C_COLOR, ft_strlen(parts[0])) == 0)
			if (parse_color(&e->ceil_color, parts) == FAIL)
				err_exit(ERR_WRONG_COLOR);
	}
	// TODO: free split
	/*
	i = 0;
	while (parts[i])
	{
		printf("%s : ", parts[i]);
		i++;
	}
	printf("\n");
	*/
	return (OK);
}

int		parse_cub_file(t_vars *e)
{
	char	**map;
	char	*line;
	int		result;
	
	e->wall_color = WALL_COLOR;
	e->floor_color = FLOOR_COLOR;
	e->ceil_color = CEIL_COLOR;

	while ((result = get_next_line(e->fd, &line)))
	{
		if (parse_line(e, line) == FAIL)
		{
			return (FAIL);
		}
		printf("%s\n", line);
	}
	//if (e->parsed != PARSE_COMPL)
	//	err_exit(ERR_PARSE_FILE);
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
	//e->pl_x = 1 * SCALE + SCALE / 2;
	//e->pl_y = 2 * SCALE + SCALE / 2;
	e->pl_x = 1 + 0.5;
	e->pl_y = 4 + 0.5;
	e->pl_ang = 90;
	return (OK);
}

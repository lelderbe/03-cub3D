/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:11:01 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 16:37:35 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_r(t_cub *e, char **parts)
{
	if (e->map_parse_started)
		err_exit(ERR_PARSE_FILE);
	if (parts[1] && parts[2] && !parts[3])
	{
		// TODO: if > MAX then = MAX
		e->width = ft_atoi(parts[1]);
		e->height = ft_atoi(parts[2]);
		if (!(e->width <= 0 || e->height <= 0))
			return (OK);
	}
	return (err_exit(ERR_WRONG_RES));
}

static int	parse_texture(t_cub *e, t_img *tex, char **parts)
{
	if (e->map_parse_started)
		err_exit(ERR_PARSE_FILE);
	if (parts[1] && !parts[2])
	{
		if (!(tex->file = ft_strdup(parts[1])))
			err_exit(ERR_OUT_OF_MEM);
		return (OK);
	}
	return (err_exit(ERR_WRONG_TEXTURE));
}

static int	parse_color(t_cub *e, unsigned int *value, char **parts)
{
	char	**rgb;

	if (e->map_parse_started)
		err_exit(ERR_PARSE_FILE);
	if (parts[1] != 0)
	{
		if (!(rgb = ft_split(parts[1], ',')))
			err_exit(ERR_OUT_OF_MEM);
		if (rgb[0] && rgb[1] && rgb[2] && !rgb[3])
		{
			*value = create_trgb(0,
				ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
			free_split(rgb);
			return (OK);
		}
	}
	return (err_exit(ERR_WRONG_COLOR));
}

static int	parse_map_line(t_cub *e, char *line)
{
	int		i;
	t_list	*new;
	char	*content;

	if (ft_strlen(line) == 0 && !e->map_parse_started)
		return (OK);
	e->map_parse_started = 1;
	e->map_height++;
	if (ft_strlen(line) == 0)
		err_exit(ERR_INVALID_MAP);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(MAP_ALLOWED_CHARS, line[i]))
			err_exit(ERR_INVALID_MAP);
		i++;
	}
	e->map_width = ft_strlen(line) > e->map_width ?
									ft_strlen(line) : e->map_width;
	content = ft_strdup(line);
	if (!content || !(new = ft_lstnew(content)))
		return (err_exit(ERR_OUT_OF_MEM));
	ft_lstadd_back(&e->map_lst, new);
	return (OK);
}

int			parse_line(t_cub *e, char *line)
{
	char	**parts;

	if (!(parts = ft_split(line, ' ')))
		err_exit(ERR_OUT_OF_MEM);
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

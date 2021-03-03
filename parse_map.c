/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:33:45 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/03 15:24:55 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_sprites(t_cub *e)
{
	t_spr *spr;

	spr = malloc(sizeof(*spr));
	spr->x = 29.5;
	spr->y = 2.5;
	e->s = malloc(sizeof(*e->s) * (1 + 1));
	e->s[0] = spr;
	e->s[1] = 0;
}

static void	parse_pl_pos(t_cub *e, const char *pl_allowed_chars)
{
	int			x;
	int			y;
	char		*ptr;

	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if ((ptr = ft_strchr(pl_allowed_chars, e->map[y][x])) != 0)
			{
				e->pl_x = x + 0.5;
				e->pl_y = y + 0.5;
				e->pl_a = (ptr - pl_allowed_chars) * 90;
				e->pl_count++;
			}
			x++;
		}
		y++;
	}
	if (e->pl_count != 1)
		err_exit(ERR_INVALID_MAP);
}

static int	validate_map(char **map, int x, int y, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (FAIL);
	if (map[y][x] == '1')
		return (OK);
	if (map[y][x] == ' ')
		return (FAIL);
	map[y][x] = '1';
	return (validate_map(map, x - 1, y - 1, width, height) &&
		validate_map(map, x - 0, y - 1, width, height) &&
		validate_map(map, x + 1, y - 1, width, height) &&
		validate_map(map, x - 1, y - 0, width, height) &&
		validate_map(map, x + 1, y - 0, width, height) &&
		validate_map(map, x - 1, y + 1, width, height) &&
		validate_map(map, x - 0, y + 1, width, height) &&
		validate_map(map, x + 1, y + 1, width, height));
}

static char	**copy_map(char **map, unsigned height)
{
	int		i;
	char	**result;

	if (!(result = malloc(sizeof(*result) * (height + 1))))
		err_exit(ERR_OUT_OF_MEM);
	i = 0;
	while (map[i])
	{
		result[i] = ft_strdup(map[i]);
		if (!result[i])
			err_exit(ERR_OUT_OF_MEM);
		i++;
	}
	result[i] = 0;
	log_map(result);
	return (result);
}

void		parse_map(t_cub *e)
{
	int		i;
	t_list	*lst;
	char	**map;
	int		valid;

	if (!(e->map = malloc(sizeof(*e->map) * (e->map_height + 1))))
		err_exit(ERR_OUT_OF_MEM);
	i = 0;
	lst = e->map_lst;
	while (lst)
	{
		e->map[i] = lst->content;
		lst = lst->next;
		i++;
	}
	e->map[i] = 0;
	parse_pl_pos(e, PL_ALLOWED_CHARS);
	map = copy_map(e->map, e->map_height);
	valid = validate_map(map, (int)e->pl_x, (int)e->pl_y,
										e->map_width, e->map_height);
	free_split(map);
	if (!valid)
		err_exit(ERR_INVALID_MAP);
	parse_sprites(e);
}

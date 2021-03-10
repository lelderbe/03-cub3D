/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:33:45 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/10 12:02:46 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_pl_pos(t_cub *e, const char *pl_allowed_chars)
{
	int			x;
	int			y;
	char		*ptr;
	int			count;

	count = 0;
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
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		exit_cub(e, ERR_INVALID_MAP);
}

static int	chk_cell(t_cub *e, unsigned x, unsigned y)
{
	if (e->map[y][x] == ' ' || e->map[y][x] == '1')
		return (OK);
	if (y == 0 || x == 0 || y == e->map_h - 1 || x == e->map_w - 1)
		return (FAIL);
	if (e->map[y - 1][x - 1] == ' ' ||
			e->map[y - 1][x - 0] == ' ' ||
			e->map[y - 1][x + 1] == ' ' ||
			e->map[y - 0][x - 1] == ' ' ||
			e->map[y - 0][x + 1] == ' ' ||
			e->map[y + 1][x - 1] == ' ' ||
			e->map[y + 1][x - 0] == ' ' ||
			e->map[y + 1][x + 1] == ' ')
		return (FAIL);
	return (OK);
}

static int	validate_map(t_cub *e)
{
	unsigned	x;
	unsigned	y;

	y = 0;
	while (y < e->map_h)
	{
		x = 0;
		while (x < e->map_w)
		{
			if (chk_cell(e, x, y) == FAIL)
				return (FAIL);
			x++;
		}
		y++;
	}
	return (OK);
}

int			flood_fill(t_cub *e, char **map, int x, int y)
{
	if (y < 0 || y >= (int)e->map_h || x < 0 || x >= (int)e->map_w)
		return (FAIL);
	if (map[y][x] == '1' || map[y][x] == 0)
		return (OK);
	if (map[y][x] == ' ')
		return (FAIL);
	map[y][x] = '1';
	return (
		flood_fill(e, map, x - 1, y - 1) &&
		flood_fill(e, map, x - 0, y - 1) &&
		flood_fill(e, map, x + 1, y - 1) &&
		flood_fill(e, map, x - 1, y - 0) &&
		flood_fill(e, map, x + 1, y - 0) &&
		flood_fill(e, map, x - 1, y + 1) &&
		flood_fill(e, map, x - 0, y + 1) &&
		flood_fill(e, map, x + 1, y + 1));
}

void		parse_map(t_cub *e)
{
	int		i;
	t_list	*lst;

	if (!(e->map = calloc(e->map_h + 1, sizeof(*e->map))))
		exit_cub(e, ERR_OUT_OF_MEM);
	i = e->map_h - 1;
	lst = e->map_lst;
	while (lst)
	{
		if (!(e->map[i] = ft_calloc(e->map_w + 1, sizeof(**e->map))))
			exit_cub(e, ERR_OUT_OF_MEM);
		ft_memset(e->map[i], ' ', e->map_w);
		ft_memcpy(e->map[i], lst->content, ft_strlen(lst->content));
		lst = lst->next;
		i--;
	}
	parse_pl_pos(e, PL_ALLOWED_CHARS);
	if (!validate_map(e))
		exit_cub(e, ERR_INVALID_MAP);
}

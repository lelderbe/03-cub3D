/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:33:45 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 17:35:14 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_pl_pos(t_cub *e, const char *pl_allowed_chars)
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

void	parse_map(t_cub *e)
{
	int		i;
	t_list	*lst;

	//log_lst(e->map_lst);
	//printf("map max line len: %d\n", (int)e->map_w);
	//printf("map lines: %d\n", e->map_h);
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
}

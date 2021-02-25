/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:33:45 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/25 19:33:48 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_map_line(t_vars *e, char *line)
{
	int		i;
	t_list	*new;
	char	*content;

	if (ft_strlen(line) == 0 && !e->map_parse_started)
		return (OK);
	e->map_parse_started = 1;
	e->map_lines++;
	// empty -> error
	if (ft_strlen(line) == 0)
		return err_exit(ERR_INVALID_MAP);
	// wrong symbols -> error
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(MAP_ALLOWED_CHARS, line[i]))
			return err_exit(ERR_INVALID_MAP);
		i++;
	}
	e->map_max = ft_strlen(line) > e->map_max ? ft_strlen(line) : e->map_max;
	if (!(content = ft_strdup(line)) || !(new = ft_lstnew(content)))
		return err_exit(ERR_OUT_OF_MEM);
	ft_lstadd_back(&e->map_lst, new);
	return (OK);
}

void	parse_pl_pos(t_vars *e, const char *pl_allowed_chars)
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
				e->pl_ang = (ptr - pl_allowed_chars) * 90;
				e->pl_count++;
			}
			x++;
		}
		y++;
	}
	if (e->pl_count != 1)
		err_exit(ERR_INVALID_MAP);
}

void	parse_map(t_vars *e)
{
	int		i;
	t_list	*lst;

	//log_lst(e->map_lst);
	//printf("map max line len: %d\n", (int)e->map_max);
	//printf("map lines: %d\n", e->map_lines);
	if (!(e->map = malloc(sizeof(*e->map) * (e->map_lines + 1))))
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
	// more one pl -> error
	parse_pl_pos(e, PL_ALLOWED_CHARS);
}


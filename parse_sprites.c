/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:42:29 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/09 14:13:26 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_spr	*get_sprite(t_cub *e, double x, double y)
{
	t_spr	*s;

	if (!(s = malloc(sizeof(*s))))
		exit_cub(e, ERR_OUT_OF_MEM);
	s->x = x + 0.5;
	s->y = y + 0.5;
	return (s);
}

static t_list	*get_sprites_list(t_cub *e, const char *allowed_chars)
{
	int		x;
	int		y;
	t_list	*new;
	t_list	*lst;

	lst = 0;
	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if (ft_strchr(allowed_chars, e->map[y][x]))
			{
				if (!(new = ft_lstnew(get_sprite(e, x, y))))
					exit_cub(e, ERR_OUT_OF_MEM);
				ft_lstadd_back(&lst, new);
			}
			x++;
		}
		y++;
	}
	return (lst);
}

void			parse_sprites(t_cub *e)
{
	t_list	*spr_list;
	t_list	*lst;
	int		i;

	spr_list = get_sprites_list(e, SPRITE_SYMBOLS);
	e->s_count = ft_lstsize(spr_list);
	if (!(e->s = malloc(sizeof(*e->s) * (e->s_count + 1))))
		exit_cub(e, ERR_OUT_OF_MEM);
	i = 0;
	lst = spr_list;
	while (lst)
	{
		e->s[i] = lst->content;
		lst = lst->next;
		i++;
	}
	e->s[i] = 0;
	ft_lstclear(&spr_list, 0);
}

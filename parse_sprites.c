/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:42:29 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/04 21:04:19 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_sprites_list(t_cub *e, const char *allowed_chars)
{
	int		x;
	int		y;
	t_list	*new;
	t_spr	*s;

	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if (ft_strchr(allowed_chars, e->map[y][x]))
			{
				if (!(s = malloc(sizeof(*s))))
					err_exit(ERR_OUT_OF_MEM);
				s->x = x + 0.5;
				s->y = y + 0.5;
				if (!(new = ft_lstnew(s)))
					err_exit(ERR_OUT_OF_MEM);
				ft_lstadd_back(&e->spr_list, new);
			}
			x++;
		}
		y++;
	}
}

void		parse_sprites(t_cub *e)
{
	t_list	*lst;
	int		i;

	get_sprites_list(e, SPRITE_SYMBOLS);
	e->s_count = ft_lstsize(e->spr_list);
	if (!(e->s = malloc(sizeof(*e->s) * (e->s_count + 1))))
		err_exit(ERR_OUT_OF_MEM);
	i = 0;
	lst = e->spr_list;
	while (lst)
	{
		e->s[i] = lst->content;
		lst = lst->next;
		i++;
	}
	e->s[i] = 0;
}

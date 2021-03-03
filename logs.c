/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:20:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/03 16:32:28 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	log_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	log_map2(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	log_pl(t_cub *e)
{
	printf("x: %6.2f (%d) y: %6.2f (%d) angle: %6.2f\n",
		e->pl_x, (int)round(e->pl_x * TILE),
		e->pl_y, (int)round(e->pl_y * TILE), e->pl_a);
}

void	log_img(t_img *img)
{
	printf("addr: %p\n", img->addr);
	printf("bits_per_pixel: %d\n", img->bpp);
	printf("line_length: %d\n", img->len);
	printf("endian: %d\n", img->endian);
	printf("width: %d\n", img->width);
	printf("height: %d\n", img->height);
}

void	log_lst(t_list *lst)
{
	printf("------list---------\n");
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void	log_eq(char *s1, char *s2)
{
	printf("compare: |%s| vs |%s|\n", s1, s2);
}

void	log_bmp(t_bmp *bmp)
{
	printf("width: %d, height: %d, bpp: %d\n",
		bmp->info.image_width, bmp->info.image_height, bmp->info.bpp);
}

void	log_sprites(t_spr **s)
{
	int i;

	printf("======== Sprites =============\n");
	i = 0;
	while(s[i])
	{
		//printf("sprite x: %d, y: %d\n", (int)s[i]->x, (int)s[i]->y);
		printf("sprite x: %6.2f, y: %6.2f\n", s[i]->x, s[i]->y);
		i++;
	}
}

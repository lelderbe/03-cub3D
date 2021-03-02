/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:20:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/02 10:28:41 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	log_map(t_cub *e)
{
	int	i;

	i = 0;
	while (e->map[i])
	{
		printf("%s\n", e->map[i]);
		i++;
	}
}

void	log_map2(t_cub *e)
{
	int	i;
	int	j;

	i = 0;
	while (e->map[i])
	{
		j = 0;
		while (e->map[i][j])
		{
			printf("%c ", e->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	log_pl(t_cub *e)
{
	//printf("x: %d y: %d angle: %6.2f\n", e->pl_x, e->pl_y, e->pl_ang);
	printf("x: %6.2f (%d) y: %6.2f (%d) angle: %6.2f\n",
		e->pl_x, (int)round(e->pl_x * TILE), e->pl_y, (int)round(e->pl_y * TILE), e->pl_ang);
}

void	log_img(void *addr, int bpp, int len, int endian)
{
	printf("addr: %p\n", addr);
	printf("bits_per_pixel: %d\n", bpp);
	printf("line_length: %d\n", len);
	printf("endian: %d\n", endian);
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

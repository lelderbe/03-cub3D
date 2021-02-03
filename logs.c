/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:20:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/03 13:15:18 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	log_map(t_vars *e)
{
	int	i;

	i = 0;
	while (e->map[i])
	{
		printf("%s\n", e->map[i]);
		i++;
	}
}

void	log_map2(t_vars *e)
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

void	log_pl(t_vars *e)
{
	printf("x: %d y: %d angle: %6.2f\n", e->pl_x, e->pl_y, e->pl_ang);
}

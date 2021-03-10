/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:04:11 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/10 10:08:48 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			cub_atoi(const char *str)
{
	int	result;
	int sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r')
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0') < result ?
						INT_MAX : result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int			check_atoi(char *s, int min, int max)
{
	int	value;
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FAIL);
		i++;
	}
	value = cub_atoi(s);
	if (value >= min && value <= max)
		return (OK);
	return (FAIL);
}

static void	free_textures(t_cub *e)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (e->w[i].file)
		{
			free(e->w[i].file);
			if (e->w[i].img)
				mlx_destroy_image(e->mlx, e->w[i].img);
		}
		i++;
	}
	free(e->sprite.file);
	if (e->sprite.img)
		mlx_destroy_image(e->mlx, e->sprite.img);
}

void		free_resources(t_cub *e)
{
	if (e->win)
		mlx_destroy_window(e->mlx, e->win);
	ft_lstclear(&e->map_lst, free);
	free_split(e->map);
	if (e->main.img)
		mlx_destroy_image(e->mlx, e->main.img);
	if (e->mp.img)
		mlx_destroy_image(e->mlx, e->mp.img);
	free_textures(e);
	free(e->atans);
	free(e->z);
	free_split((char **)e->s);
}

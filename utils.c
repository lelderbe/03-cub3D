/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:02:55 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/27 20:32:07 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		eq(char *s1, char *s2)
{
	int	len;

	//printf("compare: |%s| vs |%s|\n", s1, s2);
	//log_eq(s1, s2);
	if (!s1 || !s2)
		return (FAIL);
	len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
	if (ft_strncmp(s1, s2, len) == 0)
		return (OK);
	return (FAIL);
}

int		err_exit(char *err)
{
	ft_putendl_fd(ERROR, 1);
	ft_putendl_fd(err, 1);
	exit (1);
}

void	free_split(char **s)
{
	long	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

double		cos_ang(double ang)
{
	return (cos(ang / 180 * M_PI));
}

double		sin_ang(double ang)
{
	return (-sin(ang / 180 * M_PI));
}


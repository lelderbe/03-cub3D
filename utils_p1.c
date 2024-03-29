/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:02:55 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/09 18:43:46 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		eq(char *s1, char *s2)
{
	int	len;

	if (!s1 || !s2)
		return (FAIL);
	len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
	if (ft_strncmp(s1, s2, len) == 0)
		return (OK);
	return (FAIL);
}

int		exit_cub(t_cub *e, char *err)
{
	if (e)
		free_resources(e);
	if (err)
	{
		ft_putendl_fd(ERROR, 1);
		ft_putendl_fd(err, 1);
		exit(1);
	}
	exit(0);
}

void	free_split(char **s)
{
	long	i;

	i = 0;
	while (s && s[i])
		free(s[i++]);
	free(s);
}

double	cos_a(double ang)
{
	if (ang >= 360)
		ang = ang - 360;
	if (ang < -360)
		ang = 360 + ang;
	return (cos(ang / 180 * M_PI));
}

double	sin_a(double ang)
{
	if (ang >= 360)
		ang = ang - 360;
	if (ang < -360)
		ang = 360 + ang;
	return (-sin(ang / 180 * M_PI));
}

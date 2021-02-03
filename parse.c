/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:46:54 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/03 13:09:44 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_params(int argc, char **argv, t_vars *e)
{
	(void)argv;

	if (argc < 2 || argc > 3)
	{
		//error
		ft_putendl_fd(ERROR, 1);
		ft_putendl_fd(ERROR_ARGS_COUNT, 1);
		return (FAIL);
	}
	e->cub_filename = argv[1];
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], SAVE_OPTION, 10) == 0)
		{
			e->save_option = 1;
			printf("save_option = 1\n");
		}
		else
		{
			//error argument
			printf("wrong second option\n");
			return (FAIL);
		}
	}
	return (OK);
}

int		parse_cub_file(t_vars *e)
{
	char	**map;

	map = malloc(sizeof(*map) * (4 + 1));
	map[0] = ft_strdup("1111");
	map[1] = ft_strdup("1001");
	map[2] = ft_strdup("1N01");
	map[3] = ft_strdup("1111");
	map[4] = 0;
	e->width = 640;
	e->height = 480;
	e->map = map;
	e->pl_x = 1 * SCALE + SCALE / 2;
	e->pl_y = 2 * SCALE + SCALE / 2;
	e->pl_ang = 90;
	return (OK);
}

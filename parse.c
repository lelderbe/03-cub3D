/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:46:54 by lelderbe          #+#    #+#             */
/*   Updated: 2021/02/02 16:35:31 by lelderbe         ###   ########.fr       */
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
	e->width = 640;
	e->height = 480;
	return (OK);
}

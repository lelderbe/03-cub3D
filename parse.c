/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:08:25 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/04 21:11:46 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		parse_arguments(int argc, char **argv, t_cub *e)
{
	if (argc < 2 || argc > 3)
		err_exit(ERR_ARGS_COUNT);
	e->cub_filename = argv[1];
	e->fd = open(e->cub_filename, O_RDONLY);
	if (e->fd == -1)
		err_exit(ERR_OPEN_FILE);
	if (argc == 3)
	{
		if (eq(argv[2], SAVE_OPTION))
			e->save_option = 1;
		else
			err_exit(ERR_INVALID_ARG);
	}
}

static void	prepare_cub(t_cub *e)
{
	int i;

	e->half_w = e->width / 2;
	e->half_h = e->height / 2;
	e->dpp = 1.0 * e->half_w / tan((FOV / 2) * M_PI / 180) / 1;
	if (!(e->atans = malloc(sizeof(*e->atans) * e->width)))
		err_exit(ERR_OUT_OF_MEM);
	if (!(e->z = malloc(sizeof(*e->z) * e->width)))
		err_exit(ERR_OUT_OF_MEM);
	i = 0;
	while (i < e->width)
	{
		e->atans[i] = atan((i - e->half_w) / e->dpp) / M_PI * 180;
		i++;
	}
	e->map_visible = 0;
}

void		parse_cub_file(t_cub *e)
{
	char	*line;
	int		result;

	while ((result = get_next_line(e->fd, &line)))
	{
		parse_line(e, line);
		free(line);
	}
	if (ft_strlen(line) > 0)
		parse_line(e, line);
	free(line);
	if ((unsigned char)e->parsed != PARSE_OPT_COMPLETE)
		err_exit(ERR_PARSE_FILE);
	parse_map(e);
	prepare_cub(e);
	printf("e->width: %d, e->height: %d\n", e->width, e->height);
	printf("e->dpp: %6.2f\n", e->dpp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:08:25 by lelderbe          #+#    #+#             */
/*   Updated: 2021/03/05 15:36:50 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		parse_arguments(int argc, char **argv, t_cub *e)
{
	if (argc < 2)
		err_exit(ERR_NO_CUB_FILE);
	if (!(ft_strlen(argv[1]) > 4 &&
		ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) == 0))
		err_exit(ERR_NO_CUB_FILE);
	e->cub_filename = argv[1];
	e->fd = open(e->cub_filename, O_RDONLY);
	if (e->fd == -1)
		err_exit(ERR_OPEN_FILE);
	if (argc >= 3)
	{
		if (eq(argv[2], SAVE_OPTION))
			e->save_option = 1;
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
		if (result == -1)
			err_exit(ERR_PARSE_FILE);
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
}

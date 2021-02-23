/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:12:44 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/17 14:51:47 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_result(int count, char **remainder, char **line, char *found)
{
	if (!found)
	{
		if (count == -1)
		{
			free(*remainder);
			*remainder = 0;
			return (-1);
		}
		if (count == 0)
		{
			*line = *remainder;
			*remainder = 0;
			return (0);
		}
	}
	found[0] = '\0';
	*line = *remainder;
	if (!(*remainder = ft_strjoin(found + 1, 0)))
		return (-1);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char *remainder;
	char		*buf;
	char		*found;
	int			count;
	char		*ptr;

	if (!line || BUFFER_SIZE <= 0 ||
		!(buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!(found = ft_strchr(remainder, '\n')) &&
		(count = read(fd, buf, BUFFER_SIZE)) != -1)
	{
		buf[count] = '\0';
		ptr = remainder;
		remainder = ft_strjoin(remainder, buf);
		free(ptr);
		if (!remainder)
			count = -1;
		if (count == 0 || count == -1)
			break ;
	}
	free(buf);
	return (get_result(count, &remainder, line, found));
}

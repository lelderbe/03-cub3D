/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:48:38 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/10 11:26:12 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	get_parts_count(char const *s, char c)
{
	long	count;
	int		out;

	count = 0;
	out = 1;
	while (*s)
	{
		if (*s == c)
			out = 1;
		else if (out)
		{
			count++;
			out = 0;
		}
		s++;
	}
	return (count);
}

static void	free_split(char **s)
{
	long	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static char	*get_next_part(char const *s, char c)
{
	char	*result;
	long	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	result = (char *)malloc(sizeof(*result) * (i + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, s, i + 1);
	return (result);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	long	parts;
	long	part;

	if (!s)
		return (0);
	parts = get_parts_count(s, c);
	if (!(result = (char **)ft_calloc(parts + 1, sizeof(*result))))
		return (0);
	part = 0;
	while (part < parts)
	{
		if (*s == c)
			s++;
		else
		{
			if (!(result[part] = get_next_part(s, c)))
			{
				free_split(result);
				return (0);
			}
			s = s + ft_strlen(result[part++]);
		}
	}
	return (result);
}

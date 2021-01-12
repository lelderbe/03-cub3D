/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:33:55 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/09 12:54:39 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	length;
	size_t	i;

	length = ft_strlen(s);
	i = 0;
	while (i <= length)
	{
		if (*(char *)(s + length - i) == (char)c)
			return ((char *)(s + length - i));
		i++;
	}
	return (0);
}

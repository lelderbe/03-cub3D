/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:47:31 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/09 13:07:34 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if ((len == 0 && needle_len == 0) || (!*haystack && !*needle))
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		if (needle_len > len)
			break ;
		if (ft_strncmp(needle, haystack, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}

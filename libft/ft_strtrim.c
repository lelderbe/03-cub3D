/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:19:26 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/18 14:09:48 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	j = j ? j - 1 : 0;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	size = (j >= i) ? j - i + 1 : 0;
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	ft_memcpy(result, s1 + i, size);
	result[size] = '\0';
	return (result);
}

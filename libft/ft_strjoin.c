/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:04:25 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/08 19:25:40 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*ptr;
	size_t	length;

	if (!s1 && !s2)
		return (0);
	length = (s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0);
	result = malloc(sizeof(*result) * (length + 1));
	if (!result)
		return (0);
	ptr = result;
	if (s1)
		while ((*ptr = *s1++))
			ptr++;
	if (s2)
		while ((*ptr = *s2++))
			ptr++;
	return (result);
}

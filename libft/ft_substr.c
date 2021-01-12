/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:00:00 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/08 19:28:34 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (0);
	result = ft_calloc(len + 1, sizeof(*result));
	if (!result)
		return (0);
	if (ft_strlen(s) <= start)
		return (result);
	ft_memcpy(result, s + start, len);
	return (result);
}

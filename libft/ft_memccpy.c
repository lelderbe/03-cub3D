/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:22:27 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/12 14:11:25 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n)
	{
		*(char *)dst = *(char *)src;
		if (*(unsigned char *)src == (unsigned char)c)
			return (++dst);
		dst++;
		src++;
		n--;
	}
	return (0);
}

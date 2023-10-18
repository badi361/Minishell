/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:49:26 by bguzel            #+#    #+#             */
/*   Updated: 2022/10/31 19:02:19 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*sourc;
	size_t			i;

	sourc = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	if (!len || dst == src)
		return (dest);
	if (dst < src)
	{
		while (len > 0)
		{
			dest[i] = sourc[i];
			i++;
			len--;
		}
	}
	else
	{
		while (len--)
			dest[len] = sourc[len];
	}
	return (dest);
}

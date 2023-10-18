/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:55:44 by bguzel            #+#    #+#             */
/*   Updated: 2022/10/27 19:54:40 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*k;
	const unsigned char	*l;

	i = 0;
	k = (const unsigned char *)s1;
	l = (const unsigned char *)s2;
	while (i < n)
	{
		if (k[i] != l[i])
		{
			return (k[i] - l[i]);
		}
		i++;
	}
	return (0);
}

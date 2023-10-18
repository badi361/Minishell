/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:37:25 by bguzel            #+#    #+#             */
/*   Updated: 2022/10/28 12:02:02 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			*k;

	k = (char *)s;
	c = (unsigned char)c;
	i = 0;
	while (k[i])
	{
		if (k[i] == c)
			return (&k[i]);
		i++;
	}
	if (c == 0)
		return (&k[i]);
	return (0);
}

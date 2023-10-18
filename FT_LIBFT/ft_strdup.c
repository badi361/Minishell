/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:20:09 by bguzel            #+#    #+#             */
/*   Updated: 2022/10/28 13:02:22 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		k;
	int		i;
	char	*str;

	str = (char *)s1;
	i = ft_strlen(str);
	s2 = (char *)malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (0);
	k = 0;
	while (str[k])
	{
		s2[k] = str[k];
		k++;
	}
	s2[k] = '\0';
	return (s2);
}

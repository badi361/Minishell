/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:41:51 by bguzel            #+#    #+#             */
/*   Updated: 2022/10/31 20:08:19 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	m;
	char	*result;

	i = 0;
	result = (char *)haystack;
	if (!needle[i])
		return (result);
	else if (len == 0)
		return (0);
	while (result[i] != '\0' && i < len)
	{
		m = 0;
		while ((needle[m] && result[i + m] == needle[m] && (i + m < len)))
			m++;
		if (needle[m] == '\0')
			return (&result[i]);
		i++;
	}
	return (0);
}

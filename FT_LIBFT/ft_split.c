/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:40:15 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 20:39:00 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_counter(char const *s1, char a)
{
	int		k;
	int		i;
	int		l;

	k = 0;
	i = 0;
	l = 1;
	while (s1[i])
	{
		if (s1[i] != a && l == 1)
		{
			k++;
			l = 0;
		}
		else if (s1[i] == a)
		{
			l = 1;
		}
		i++;
	}
	return (k);
}

int	word_len(const char *src, char d)
{
	int		dc;
	int		i;

	i = 0;
	dc = 0;
	while (src[i] == d)
		i++;
	while (src[i] != d && src[i])
	{
		i++;
		dc++;
	}
	return (dc);
}

char	*stringer(char const *src, char b)
{
	char	*kel;
	int		i;

	i = 0;
	kel = (char *)malloc(sizeof(char) * word_len(src, b) + 1);
	while (*src && *src != b)
	{
		kel[i] = *(src++);
		i++;
	}
	kel[i] = '\0';
	return (kel);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**result;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	size = word_counter(s, c);
	result = malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < size && s[i])
	{
		while (s[i] == c)
			i++;
		result[j] = stringer(&s[i], c);
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

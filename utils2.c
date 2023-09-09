/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:36:33 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 20:36:34 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*only_dolar(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = '$';
	str[1] = 0;
	return (str);
}

int	ft_strncmp_v3(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s2)
		return (1);
	while (i < n && ((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i]
			|| (unsigned char)s1[i] < (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen_v2(char *str, char q, int i)
{
	while (str[i] && str[i] != q)
		i++;
	return (i);
}

int	rdr_pipe_return(void)
{
	printf("minishell: syntax error near unexpected token `newline'\n");
	g_var.exit_code = 258;
	return (1);
}

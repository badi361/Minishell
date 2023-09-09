/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:26:38 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 15:41:35 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_back(char *str)
{
	int		i;
	int		l;
	char	*ktm;

	l = 0;
	cd_helper(str);
	i = ft_strlen(str) - 1;
	if (str[i] == '/')
		i--;
	while (str[i] != '/' && i >= 0)
		i--;
	ktm = malloc(sizeof(char) * (i + 2));
	while (l <= i)
	{
		ktm[l] = str[l];
		l++;
	}
	ktm[l] = '\0';
	cd_helper_v2(ktm);
}

void	cd_tilde(char *str)
{
	int		i;
	int		counter;
	char	*ktm;

	counter = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			counter += 1;
		if (counter == 3)
			break ;
	}
	ktm = malloc(sizeof(char) * i);
	counter = -1;
	if (malloc_path(i, str) == 0)
	{
		chdir(g_var.path);
		free(ktm);
		return ;
	}
	while (++counter < i)
		ktm[counter] = str[counter];
	ktm[counter] = '\0';
	cd_helper_v2(ktm);
}

int	malloc_path(int i, char *str)
{
	static int	flag;
	int			k;

	if (flag == 1)
		return (0);
	flag = 0;
	k = 0;
	g_var.path = (char *)malloc(sizeof(char) * i);
	while (k < i)
	{
		g_var.path[k] = str[k];
		k++;
	}
	g_var.path[k] = '\0';
	flag = 1;
	return (1);
}

void	cd_next(char *str, char *next)
{
	int		i;
	char	*ktm;
	int		t;

	t = -1;
	i = -1;
	ktm = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(next) + 1));
	while (str[++i])
		ktm[i] = str[i];
	ktm[i++] = '/';
	while (next[++t])
		ktm[i++] = next[t];
	ktm[i] = '\0';
	if (chdir(ktm) != 0)
		no_such(next);
	else
		cd_helper_v2(ktm);
}

void	cd_helper(char *str)
{
	int	result;

	result = find_path("OLDPWD");
	free(g_var.env[result]);
	free(g_var.export[result]);
	g_var.env[result] = ft_strjoin("OLDPWD=", str);
	g_var.export[result] = ft_strjoin("OLDPWD=", str);
}

#include "minishell.h"

void	cd_back(char *str)
{
    int	i;
	int	l;
	char *ktm;

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
	chdir(ktm);
	cd_helper_v2(ktm);
	free(ktm);
}

void	cd_tilde(char *str)
{
	int	i;
	int counter;
	char *ktm;

	counter = 0;
	i = 0;
	cd_helper(str);
	while (str[i])
	{
		if (str[i] == '/')
			counter += 1;
		if (counter == 3)
			break ;
		i++;
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
	chdir(ktm);
	cd_helper_v2(ktm);
	free(ktm);
}

int	malloc_path(int i, char *str)
{
	static int	flag;
	int k;

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
	int	i;
	char *ktm;
	int t;

	t = 0;
	i = 0;
	cd_helper(str);
	ktm = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(next) + 1));
	while (str[i])
	{
		ktm[i] = str[i];
		i++;
	}
	ktm[i] = '/';
	i++;
	while (next[t])
	{
		ktm[i] = next[t];
		i++;
		t++;
	}
	ktm[i] = '\0';
	if (chdir(ktm) != 0)
		no_such(next);
	else
		cd_helper_v2(ktm);
	free(ktm);
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

void	cd_helper_v2(char *str)
{
	int	result;

	result = find_path("PWD");
	free(g_var.env[result]);
	free(g_var.export[result]);
	g_var.env[result] = ft_strjoin("PWD", str);
	g_var.export[result] = ft_strjoin("PWD", str);
}
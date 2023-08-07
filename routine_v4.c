#include "minishell.h"

void	split_env(void)
{
	int i;
    int	k;
	char **str;
	int	t;

	i = 0;
	k = find_path("PATH=");
	str = ft_split(&g_var.env[k][5], ':');
	g_var.env_path = (char **)malloc(sizeof(char *) * (ft_strlen_v3(&g_var.env[k][5], ':') + 1));
	while (i < ft_strlen_v3(&g_var.env[k][5], ':'))
	{
		t = 0;
		g_var.env_path[i] = malloc(sizeof(char) * ft_strlen(str[i]) + 1);
		while (str[i][t])
		{
			g_var.env_path[i][t] = str[i][t];
			t++;
		}
		free(str[i]);
		g_var.env_path[i][t] = '\0';
		i++;
	}
	free(str);
	g_var.env_path[i] = NULL;
}

int	search_cmd(void) //fork ekrana birşey yazdırmayan komutlara gitmeyecek. UNUTMA fork oluştur
{
	int	i;
	int result;

	i = 0;
	while (g_var.cmds[i]->str[0])
	{
		result = agree_cmd(g_var.cmds[i]->str[0]);
		if (result == 1)
		{
			ft_echo(i);
			return (0);
		}
		if (result == 2)
		{
			search_on_env(i);
			return (0);
		}
		if (result == 3)
		{
			search_on_env(i);
			return (0);
		}
		i++;
	}
	return (0);
}

int	agree_cmd(char *str)
{
	int size;

	size = ft_strlen(str);
	if (ft_strncmp_v3(str, "echo", size) == 0)
		return (1);
	if (ft_strncmp_v3(str, "pwd", size) == 0)
		return (2);
	if (ft_strncmp_v3(str, "ls", size) == 0)
		return (3);
	if (ft_strncmp_v3(str, "env", size) == 0)
		return (4);
	if (ft_strncmp_v3(str, "export", size) == 0)
		return (5);
	if (ft_strncmp_v3(str, "cd", size) == 0)
		return (6);
	if (ft_strncmp_v3(str, "exit", size) == 0)
		return (7);
	if (ft_strncmp_v3(str, "unset", size) == 0)
		return (8);
	return (0);
}

void	ft_echo(int	i)
{
	int result;

	if (just_echo(i) == 1)
	{
		printf("\n");
		return ;
	}
	result = pass_nl(i);
	if (g_var.cmds[i]->str[result] == NULL)
	{
		printf("\n");
		return ;
	}
	while (g_var.cmds[i]->str[result])
	{
		printf("%s", g_var.cmds[i]->str[result]);
		result++;
		if (g_var.cmds[i]->str[result] != NULL)
			printf(" ");
	}
	if (g_var.nl_flag == 0)
		printf("\n");
	else
		g_var.nl_flag = 0;
}

int	just_echo(int i)
{
	int	k;
	int counter;

	counter = 0;
	k = 0;
	while (g_var.cmds[i]->str[k])
	{
		k++;
		counter++;
	}
	return (counter);
}

int	pass_nl(int k)
{
	int i;
	int l;

	l = 1;
	while (g_var.cmds[k]->str[l])
	{
		if (g_var.cmds[k]->str[l][0] == '-' && g_var.cmds[k]->str[l][1] == 'n')
		{
			i = 2;
			while (g_var.cmds[k]->str[l][i] == 'n')
				i++;
			if (g_var.cmds[k]->str[l][i] != '\0')
				return (l);
			else
				g_var.nl_flag = 1;
		}
		else
			return (l);
		l++;
	}
	return (l);
}
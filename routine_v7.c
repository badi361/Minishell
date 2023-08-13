#include "minishell.h"

char	*add_quote_v2(char *str)
{
	char *result;
	int	i;
	int	l;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 3));
	while (str[i] != '=')
	{
		result[i] = str[i];
		i++;
	}
	l = i;
	result[i++] = '=';
	result[i++] = '"';
	while (str[l])
	{
		result[i] = str[l];
		l++;
		i++;
	}
	result[i++] = '"';
	result[i] = '\0';
	return (result);
}

int	find_equal_v2(char *str)
{
	int	i;
	int flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (0);
	else
		return (1);
}

void	new_env(int	index, int k, int l)
{
	int	i;
	char **str;

	i = 0;
	if (index == -1)
	{
		str = malloc(sizeof(char *) * (g_var.env_size + 2));
		while (g_var.env[i])
		{
			str[i] = ft_strdup(g_var.env[i]);
			free(g_var.env[i]);
			i++;
		}
		str[i] = ft_strdup(g_var.cmds[k]->str[l]);
		free(g_var.env);
		g_var.env = str;
		g_var.env_size += 1;
	}
	else
	{
		free(g_var.env[index]);
		g_var.env[index] = ft_strdup(g_var.cmds[k]->str[l]);
	}
}

void	search_cmd_v2(int result, int i)
{
		if (result == 6)
			ft_cd(i);
		if (result == 7)
		{
			if (g_var.cmds[i]->str[1] == NULL)
				print_export();
			else
				ft_export(i - 1);
		}
		if (result == 8)
			ft_unset(i);
}

void	ft_unset(int i)
{
	int	k;
	int index1;
	int index2;

	k = 1;
	while (g_var.cmds[i]->str[k])
	{
		index1 = adasdad(i, k);
		index2 = adasdad_v2(i, k);
		refresh_env(index1);
		refresh_export(index2);
		k++;
	}
}

int	adasdad(int i, int k)
{
	int	t;
	char *str;

	t = 0;
	while (g_var.env[t])
	{
		str = find_equal_v3(g_var.env[t]);
		if (!ft_strncmp_v3(str, g_var.cmds[i]->str[k], ft_strlen(str)))
		{
			free(str);
			return (t);
		}
		t++;
	}
	free(str);
	return (-1);
}

int	adasdad_v2(int i, int k)
{
	int	t;
	char *str;

	t = 0;
	while (g_var.export[t])
	{
		str = find_equal_v3(g_var.export[t]);
		if (!ft_strncmp_v3(str, g_var.cmds[i]->str[k], ft_strlen(str)))
		{
			free(str);
			return (t);
		}
		t++;
	}
	free(str);
	return (-1);
}
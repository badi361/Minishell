#include "minishell.h"

int	agree_cmd_v2(char *str, int size)
{
	if (ft_strncmp_v3(str, "exit", size) == 0)
		return (4);
	else if (ft_strncmp_v3(str, "exit", 4) == 0)
	{
		print_error(str);
		return (-1);
	}
	if (ft_strncmp_v3(str, "env", size) == 0)
		return (5);
	else if (ft_strncmp_v3(str, "env", 3) == 0)
	{
		print_error(str);
		return (-1);
	}
	if (ft_strncmp_v3(str, "cd", size) == 0)
		return (6);
	else if (ft_strncmp_v3(str, "cd", 2) == 0)
	{
		print_error(str);
		return (-1);
	}
	return(agree_cmd_v3(str, size));
}

int	agree_cmd_v3(char *str, int size)
{
	if (ft_strncmp_v3(str, "export", size) == 0)
		return (7);
	else if (ft_strncmp_v3(str, "export", 6) == 0)
	{
		print_error(str);
		return (-1);
	}
	if (ft_strncmp_v3(str, "unset", size) == 0)
		return (8);
	else if (ft_strncmp_v3(str, "unset", 5) == 0)
	{
		print_error(str);
		return (-1);
	}
	return (0);
}

void	print_export(void)
{
	int	i;
	int	k;

	k = 0;
	while (g_var.export[k])
	{
		printf("declare -x ");
		i = 0;
		while (g_var.export[k][i])
		{
			if (g_var.export[k][i] != '=')
				printf("%c", g_var.export[k][i]);
			else
			{
				printf("=%c", '"');
				printf("%s", &g_var.export[k][++i]);
				printf("%c\n", '"');
				break ;
			}
			i++;
		}
		k++;
	}
}

void	ft_export(int k)
{
	int	i;
	char *str;

	i = 1;
	while (g_var.cmds[k]->str[i])
	{
		if (ft_isalpha(g_var.cmds[k]->str[i][0]))
		{
			str = find_equal(g_var.cmds[k]->str[i]);
			if (find_path(str) != -1)
			{
				g_var.env[find_path(str)]
			}
		}
		else
			printf("minishell: export: %s: not a valid identifier\n",
				g_var.cmds[0]->str[i]);
	}
}

void	new_env(int	k, char *data, int l)
{
	int	i;
	char **str;

	i = 0;
	if (k == -1)
	{

	}
	else
	{
		str = malloc(sizeof(char *) * (g_var.env_size + 1));
		while (g_var.env[i])
		{
			if (i == k - 1) // index
			{
				str[i] = ft_strdup(g_var.cmds[l]->str)
			}
			str[i] = ft_strdup(g_var.env[i]);
		}
	}
}

char	*new_env_help(int k)
{
	int	i;
	char *str;
	int flag;

	flag = 0;
	i = 0;
	while (g_var.cmds[k]->str[1][i])
	{
		if (g_var.cmds[k]->str[1][i] == '"')
		{
			flag += 1;
			i++;
			while (g_var.cmds[k]->str[1][i] != '"' && g_var.cmds[k]->str[1][i])
				i++;
			if (g_var.cmds[k]->str[1][i] == '"')
				flag = 2;
		}
		i++;
	}
	if (flag == 1)
		printf("syntax error token %c", '"');
	else if (flag == 2)
	str = malloc(sizeof(char) * i + 1);
}

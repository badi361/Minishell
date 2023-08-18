#include "minishell.h"

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
				printf("%c", '"');
				break ;
			}
			i++;
		}
		printf("\n");
		k++;
	}
}

void	ft_export(int k)
{
	int	i;
	char *str;

	i = 1;
	while (g_var.cmds[++k])
		while (g_var.cmds[k]->str[i])
		{
			if (ft_isalpha(g_var.cmds[k]->str[i][0]))
			{
				str = find_equal(g_var.cmds[k]->str[i]);
				if (find_equal_v2(g_var.cmds[k]->str[i]))
				{
					new_export(find_path_v2(str), k, i);
					new_env(find_path(str), k, i);
				}
				else
					new_export(find_path_v2(str), k, i);
				free(str);
			}
			else
				printf("minishell: export: %s: not a valid identifier\n",
					g_var.cmds[0]->str[i]);
				i++;
		}
}

void	new_export(int	index, int k, int l)
{
	int	i;
	char **str;

	i = 0;
	if (index == -1)
	{
		str = malloc(sizeof(char *) * (g_var.export_size + 2));
		while (g_var.export[i])
		{
			str[i] = ft_strdup(g_var.export[i]);
			free(g_var.export[i]);
			i++;
		}
		str[i++] = ft_strdup(g_var.cmds[k]->str[l]);
		free(g_var.export);
		str[i] = NULL;
		g_var.export = str;
		g_var.export_size += 1;
	}
	else if (find_equal_v2(g_var.cmds[k]->str[l]))
	{
		free(g_var.export[index]);
		g_var.export[index] = ft_strdup(g_var.cmds[k]->str[l]);
	}
}

char	*add_quote(int k, int i)
{
	int	t;
	char *result;

	t = 0;
	int	l;
	result = malloc(sizeof(char) * (ft_strlen(g_var.cmds[k]->str[i] + 3)));
	while (g_var.cmds[k]->str[i][t] != '=')
	{
		result[t] = g_var.cmds[k]->str[i][t];
		t++;
	}
	l = t;
	result[t++] = '=';
	result[t++] = '"';
	while (g_var.cmds[k]->str[i][l])
	{
		result[t] = g_var.cmds[k]->str[i][l];
		t++;
		l++;
	}
	result[t] = '"';
	result[t + 1] = '\0';
	return (result);
}

int	rdr_env(void)
{
	link_list *tmp;
	tmp = g_var.list;
	while (tmp)
	{
		if (tmp->flag == '|')
			return (1);
		if (tmp->flag == '<' || tmp->flag == '>')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	search_on_env_v2(int k)
{
	char *str;
	int i;
	int	t;
	int	flag;

	flag = 0;
	t = 0;
	while (g_var.cmds[k])
	{
		i = 0;
		while (g_var.env_path[i])
		{
			str = ft_strjoin(g_var.env_path[i], "/");
			str = ft_strjoin(str, g_var.cmds[k]->str[0]);
			if (access(str, 0) == 0)
				execve_v1(k, t, &flag, str);
			free(str);
			i++;
		}
		t++;
		k++;
	}
	if (flag == 0)
		printf("minishell: ls: command not found\n");
}

void	execve_v1(int k, int t, int *flag, char *str)
{
	*flag = 1;
	g_var.pid[t] = fork();
	if (g_var.pid[t] == 0)
	{
		if (g_var.cmds[k]->rdr_fl == 1)
		{
			dup2(g_var.cmds[k]->f_in, STDIN_FILENO);
			close(g_var.cmds[k]->f_in);
			execve(str, g_var.cmds[k]->str, g_var.env);
			free(str);
			exit(0) ;
		}
		if (g_var.cmds[k]->rdr_fl == 2)
		{
			dup2(g_var.cmds[k]->f_out, STDOUT_FILENO);
			close(g_var.cmds[k]->f_out);
			execve(str, g_var.cmds[k]->str, g_var.env);
			free(str);
			exit(0) ;
		}
		execve_v2(k, str);
	}
}
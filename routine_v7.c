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

void	search_cmd_v2(int result, int i) // fork işlemi ile child process oluşturuluyor. main process deki işlemleri child process kopyalar. fork la child process oluştuğunda child process de dönüş değeri yani (0) olacaktir. dolayısıyla child process if bloğuna girecek. main giremeyecek ve i yi arttıracak. main child ı ne yapacak dize izler.
{
	int	t;
	g_var.pid[i] = fork();
	if (g_var.pid[i] == 0)
	{
		close_fd_2(g_var.cmds[i]);
		dup2(g_var.cmds[i]->f_in, STDIN_FILENO);
		dup2(g_var.cmds[i]->f_out, STDOUT_FILENO);
		if (result == 4)
			ft_env();
		if (result == 5)
			ft_pwd();
		if (result == 6)
			print_export();
		if (result == 7)
			ft_echo(i);
		if (result == 8)
		{
			t = split_env();
			search_on_env(i, t);
		}
			exit(0);
	}
}

void	ft_unset(int i)
{
	int	k;
	int index1;
	int index2;

	k = 1;
	while (g_var.cmds[i]->str[k])
	{
		index1 = find_on_env(i, k);
		index2 = find_on_export(i, k);
		refresh_env(index1);
		refresh_export(index2);
		k++;
	}
}

int	find_on_env(int i, int k)
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
		free(str);
		t++;
	}
	return (-1);
}

int	find_on_export(int i, int k)
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
		free(str);
		t++;
	}
	return (-1);
}

void	close_fd_2(pipe_list *cmds)
{
	int	i;

	i = 0;
	while (i < g_var.pipe_count)
	{
		if (cmds->f_in != g_var.pipe[i][0])
			close(g_var.pipe[i][0]);
		if (cmds->f_out != g_var.pipe[i][1])
			close(g_var.pipe[i][1]);
		i++;
	}
}
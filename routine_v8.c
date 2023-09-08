#include "minishell.h"

void	refresh_env(int index)
{
	int	i;
	char **result;
	int	k;

	k = 0;
	if (index == -1)
		return ;
	result = malloc(sizeof(char *) * g_var.env_size);
	i = 0;
	while (g_var.env[i])
	{
		if (i == index)
			free(g_var.env[i++]);
		if (g_var.env[i])
			result[k++] = ft_strdup(g_var.env[i]);
		else
			break ;
		free(g_var.env[i]);
		i++;
	}
	result[k] = NULL;
	free(g_var.env);
	g_var.env_size--;
	g_var.env = result;
}

void	refresh_export(int index)
{
	int	i;
	char **result;
	int	k;

	k = 0;
	if (index == -1)
		return ;
	result = malloc(sizeof(char *) * g_var.export_size);
	i = 0;
	while (g_var.export[i])
	{
		if (i == index)
			free(g_var.export[i++]);
		if (g_var.export[i])
			result[k++] = ft_strdup(g_var.export[i]);
		else
			break ;
		free(g_var.export[i]);
		i++;
	}
	result[k] = NULL;
	free(g_var.export);
	g_var.export_size--;
	g_var.export = result;
}

char	*find_equal_v3(char *str)
{
	int	size;
	char *result;
	int	i;

	size = 0;
	i = 0;
	while (str[size] != '=' && str[size])
		size++;
	result = malloc(sizeof(char) * size + 1);
	while (i < size)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	rdr_init(void)
{
	link_list *tmp;
	int	fd;

	fd = 0;
	tmp = g_var.list;
	int	k;
	k = 0;
	while (tmp)
	{
		if (tmp->flag == 'i')
		{
			fd = open(tmp->content, O_RDONLY);
			g_var.cmds[k]->f_in = fd;
		}
		if (tmp->flag == 'o')
		{
			fd = open(tmp->content, O_CREAT | O_TRUNC | O_RDWR, 0777);
			g_var.cmds[k]->f_out = fd;
		}
		if (tmp->flag == 'r')
		{
			fd = open(tmp->content, O_CREAT | O_APPEND | O_RDWR, 0777);
			g_var.cmds[k]->f_out = fd;
		}
		if (tmp->flag == 'h')
			ft_here_doc(tmp->content, k);
		if (tmp->flag == '|')
			k++;
		if (fd == -1)
		{
			g_var.cmds[k]->f_out = -1;
			fd_error(fd, tmp->content);
			return ;
		}
		tmp = tmp->next;
	}
}

void	close_fd(void)
{
	int	i;

	i = 0;
	while (i <= g_var.pipe_count)
	{
		if (g_var.cmds[i]->f_in > 1)
			close(g_var.cmds[i]->f_in);
		if (g_var.cmds[i]->f_out > 1)
			close(g_var.cmds[i]->f_out);
		i++;
	}
	i = 0;
	while (i < g_var.pipe_count)
	{
		close(g_var.pipe[i][0]);
		close(g_var.pipe[i][1]);
		i++;
	}
	i = 0;
	while (i <= g_var.pipe_count)
	{
		waitpid(g_var.pid[i], &g_var.exit_code, 0);
		if (WIFEXITED(g_var.exit_code)) // child process başarıyla tamamlandıysa true döner
			g_var.exit_code = WEXITSTATUS(g_var.exit_code); // çıkış kodunu alıyor ve aktarıyor
		i++;
	}
	unlink_to_hd();
}

void	fd_error(int fd, char *str)
{
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", str);
		g_var.exit_code = 1;
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s'\n", str);
		g_var.exit_code = 258;
	}
}

void	no_such(char *str)
{
	printf("minishell: %s: No such file or directory\n", str);
	g_var.exit_code = 127;
}
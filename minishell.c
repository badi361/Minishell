#include "minishell.h"

void	malloc_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_var.env_size = i;
	g_var.export_size = i;
	g_var.env = malloc(sizeof(char *) * (i + 1));
	g_var.export = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		g_var.export[i] = ft_strdup(env[i]);
		g_var.env[i] = ft_strdup(env[i]);
		i++;
	}
	g_var.export[i] = NULL;
	g_var.env[i] = NULL;
	g_var.exit_code = 0;
	g_var.nl_flag = 0;
}

int	routine(char *str)
{
	if (check_quote(str) || lexer_parsel(str))
	{
		free(str);
		return (1);
	}
	if (rdr_pipe_check() || rdr_pipe_check_v3() || get_commands())
	{
		free(str);
		return (2);
	}
	cmd_init();
	dup_func(0);
	rdr_flag();
	rdr_init();
	input_to_place();
	search_cmd();
	return (0);
}

char	*handle_regular(char *str, int *index)
{
	int		i;
	char	*result;

	i = *index;
	while (str[i] && !is_it_special(str[i]) && str[i] != 34 && str[i] != 39)
		i++;
	result = ft_strdup_v2(str, *index, i);
	*index = i;
	return (result);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	malloc_env(env);
	while (1)
	{
		g_var.str = readline("minishell: ");
		add_history(g_var.str);
		routine(g_var.str);
	}
}

void	search_on_env(int k)
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
			{
				flag = 1;
				g_var.pid[t] = fork();
				if (g_var.pid[t] == 0)
				{
					execve(str, g_var.cmds[k]->str, g_var.env);
					free(str);
					exit(0) ;
				}
			}
			free(str);
			i++;
		}
		t++;
		k++;
		waitpid(g_var.pid[t], &g_var.exit_code, 0);
	}
	if (flag == 0)
		printf("minishell: ls: command not found\n");
}

void	dup_func(int i)
{
	dup2(g_var.cmds[i]->f_in, STDIN_FILENO);
	dup2(g_var.cmds[i]->f_out, STDOUT_FILENO);
}

void	close_fd(pipe_list *cmds)
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
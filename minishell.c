/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:38:00 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 21:54:22 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_env(char **env)
{
	int	i;

	i = 0;
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, SIG_IGN);
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
	if (rdr_pipe_check() || rdr_pipe_check_v3() || pipe_check())
	{
		free(str);
		return (2);
	}
	rdr_flag();
	cmd_init();
	input_to_place();
	rdr_init();
	if (g_var.exit != 1)
		search_cmd();
	close_fd();
	free(str);
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
	int	result;

	(void)ac;
	(void)av;
	malloc_env(env);
	while (1)
	{
		g_var.exit = 0;
		g_var.str = readline("minishell$ ");
		if (!g_var.str)
		{
			write(1, "\033[2D", 4);
			write(1, "\033[0mexit\n", 9); 
			exit(0);
		}
		add_history(g_var.str);
		result = routine(g_var.str);
		if (g_var.exit != 1 && g_var.str[0] && result == 0) 
			leaks_destroyer();
		else if (result != 1)
			free(g_var.str);
	}
}

void	search_on_env(int k, int t)
{
	char	*str;
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	if (access(g_var.cmds[k]->str[0], 0) == 0)
		execve(g_var.cmds[k]->str[0], g_var.cmds[k]->str, g_var.env);
	else if (t == 0)
	{
		no_such(g_var.cmds[k]->str[0]);
		flag = 1;
	}
	while (g_var.env_path[++i] && flag == 0)
	{
		str = ft_strjoin(g_var.env_path[i], "/");
		str = ft_strjoin(str, g_var.cmds[k]->str[0]);
		if (access(str, 0) == 0)
		{
			flag = 1;
			execve(str, g_var.cmds[k]->str, g_var.env);
		}
		free(str);
	}
	execve_helper(flag, g_var.cmds[k]->str[0]);
}

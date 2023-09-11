/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:24:28 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/10 15:05:53 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_env(int index)
{
	int		i;
	char	**result;
	int		k;

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
	int		i;
	char	**result;
	int		k;

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
	int		size;
	char	*result;
	int		i;

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
	t_list	*tmp;
	int		fd;
	int		k;

	fd = 0;
	tmp = g_var.list;
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
		if (rdr_init_help(tmp, &k, fd))
			return ;
		tmp = tmp->next;
	}
}

void	close_fd(void)
{
	int	i;

	i = -1;
	while (++i <= g_var.pipe_count)
	{
		if (g_var.cmds[i]->f_in > 1)
			close(g_var.cmds[i]->f_in);
		if (g_var.cmds[i]->f_out > 1)
			close(g_var.cmds[i]->f_out);
	}
	i = -1;
	while (++i < g_var.pipe_count)
	{
		close(g_var.pipe[i][0]);
		close(g_var.pipe[i][1]);
	}
	i = -1;
	while (++i <= g_var.pipe_count)
	{
		waitpid(g_var.pid[i], &g_var.exit_code, 0);
		if (WIFEXITED(g_var.exit_code))
			g_var.exit_code = WEXITSTATUS(g_var.exit_code);
		if (g_var.exit_code == 2)
			g_var.ctrl_c = g_var.exit_code;
	}
}

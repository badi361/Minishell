/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:54:07 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 20:35:05 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_helper(int i)
{
	if (str_is_digit(g_var.cmds[i]->str[1])
		&& g_var.cmds[i]->str[2] != NULL)
		printf("exit\nminishell: exit: too many arguments\n");
	else if (!str_is_digit(g_var.cmds[i]->str[1]))
	{
		printf("exit\nminishell: exit: %s:numeric argument required\n",
			g_var.cmds[i]->str[1]);
		leaks_destroyer();
		free(g_var.path);
		exit(255);
	}
}

void	cd_helper_v3(int k, char *str)
{
	if (ft_strncmp_v3(g_var.cmds[k]->str[1], "..", 2) == 0)
	{
		if (g_var.cmds[k]->str[1][2])
		{
			no_such(g_var.cmds[k]->str[1]);
			return ;
		}
		cd_back(str);
	}
	else if (ft_strncmp_v3(g_var.cmds[k]->str[1], "~", 1) == 0)
	{
		if (g_var.cmds[k]->str[1][1])
		{
			no_such(g_var.cmds[k]->str[1]);
			return ;
		}
		cd_helper(str);
		cd_tilde(str);
	}
	else if (g_var.cmds[k]->str[1])
	{
		cd_helper(str);
		cd_next(str, g_var.cmds[k]->str[1]);
	}
}

int	find_on_env(int i, int k)
{
	int		t;
	char	*str;

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
	int		t;
	char	*str;

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

void	close_fd_2(t_pipe_list *cmds)
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

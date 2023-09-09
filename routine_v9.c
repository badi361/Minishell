/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:31:20 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 20:36:04 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_helper_v2(char *str)
{
	int	result;

	result = find_path("PWD");
	free(g_var.env[result]);
	free(g_var.export[result]);
	g_var.env[result] = ft_strjoin("PWD", str);
	g_var.export[result] = ft_strjoin("PWD", str);
	chdir(str);
	free(str);
}

void	signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_var.hd_flag = 2;
		g_var.exit = 1;
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
}

void	leaks_destroyer(void)
{
	int	i;

	if (g_var.pid)
		free(g_var.pid);
	i = 0;
	if (g_var.cmds)
	{
		while (g_var.cmds[i])
		{
			free(g_var.cmds[i]);
			i++;
		}
		free(g_var.cmds);
	}
	i = -1;
	if (g_var.env_path)
	{
		while (g_var.env_path[++i])
			free(g_var.env_path[i]);
		free(g_var.env_path);
	}
	if (g_var.str)
		free(g_var.str);
	leaks_destroyer_v2();
}

void	execve_helper(int flag, char *str)
{
	if (flag == 0)
	{
		print_error(str);
		exit(g_var.exit_code);
	}
}

int	just_echo(int i)
{
	int	k;
	int	counter;

	counter = 0;
	k = 0;
	while (g_var.cmds[i]->str[k])
	{
		k++;
		counter++;
	}
	return (counter);
}

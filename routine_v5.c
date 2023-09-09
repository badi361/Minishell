/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:48:23 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 19:39:36 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int i)
{
	if (g_var.cmds[i]->str[1] == NULL)
	{
		printf("exit\n");
		leaks_destroyer();
		free(g_var.path);
		exit(0);
	}
	else if (str_is_digit(g_var.cmds[i]->str[1])
		&& g_var.cmds[i]->str[2] == NULL)
	{
		printf("exit\n");
		g_var.exit_code = ft_atoi(g_var.cmds[i]->str[1]);
		leaks_destroyer();
		free(g_var.path);
		exit(g_var.exit_code);
	}
	exit_helper(i);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_var.env[i])
	{
		printf("%s\n", g_var.env[i]);
		i++;
	}
}

void	ft_pwd(void)
{
	char	p[256];

	getcwd(p, sizeof(p));
	printf("%s\n", p);
}

void	ft_cd(int k)
{
	char	str[128];

	getcwd(str, sizeof(str));
	if (g_var.cmds[k]->str[1])
		cd_helper_v3(k, str);
	else
	{
		cd_helper(str);
		cd_tilde(str);
	}
}

void	print_error(char *str)
{
	printf("minishell: %s: command not found\n", str);
	g_var.exit_code = 127;
}

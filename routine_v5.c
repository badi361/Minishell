#include "minishell.h"

void	ft_exit(int	i)
{
	if (g_var.cmds[i]->str[1] == NULL)
	{
		printf("exit\n");
		leaks_destroyer();
		free(g_var.path);
		exit(0);
	}
	else if (str_is_digit(g_var.cmds[i]->str[1]) && g_var.cmds[i]->str[2] == NULL)
	{
		printf("exit\n");
		g_var.exit_code = ft_atoi(g_var.cmds[i]->str[1]);
		leaks_destroyer();
		free(g_var.path);
		exit(g_var.exit_code);
	}
	else if (str_is_digit(g_var.cmds[i]->str[1]) && g_var.cmds[i]->str[2] != NULL)
		printf("exit\nminishell: exit: too many arguments\n");
	else if (!str_is_digit(g_var.cmds[i]->str[1]))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", g_var.cmds[i]->str[1]);
		leaks_destroyer();
		free(g_var.path);
		exit(255);
	}
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
	char str[128];

	getcwd(str, sizeof(str));
	if (g_var.cmds[k]->str[1])
	{
		if (ft_strncmp_v3(g_var.cmds[k]->str[1], "..", 2) == 0)
		{
			if (g_var.cmds[k]->str[1][2])
			{
				printf("minishell: cd: %s: No such file or directory\n", g_var.cmds[k]->str[1]);
				return ;
			}
			cd_back(str);
		}
		else if (ft_strncmp_v3(g_var.cmds[k]->str[1], "~", 1) == 0)
		{
			if (g_var.cmds[k]->str[1][1])
			{
				printf("minishell: cd: %s: No such file or directory\n", g_var.cmds[k]->str[1]);
				return ;
			}
			cd_tilde(str);
		}
		else if (g_var.cmds[k]->str[1])
			cd_next(str, g_var.cmds[k]->str[1]);
	}
	else
		cd_tilde(str);
}

void	print_error(char *str)
{
	printf("minishell: %s: command not found\n", str);
}
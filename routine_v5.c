#include "minishell.h"

void	ft_exit(int	i)
{
	if (g_var.cmds[i]->str[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (str_is_digit(g_var.cmds[i]->str[1]) && g_var.cmds[i]->str[2] == NULL)
	{
		printf("exit\n");
		exit(ft_atoi(g_var.cmds[i]->str[1]));
	}
	else if (str_is_digit(g_var.cmds[i]->str[1]) && g_var.cmds[i]->str[2] != NULL)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
	}
	else if (!str_is_digit(g_var.cmds[i]->str[1]))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required", g_var.cmds[i]->str[1]);
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
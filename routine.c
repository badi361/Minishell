#include "minishell.h"

int	lexer_parsel(char *str)
{
	int i;
	int	k;

	i = 0;
	g_var.str = ft_strtrim(str, " ");
	link_lstclear(&g_var.list);
	while (i < ft_strlen_v1(g_var.str))
	{
		while (g_var.str[i] == ' ' || g_var.str[i] == 9)
			i++;
		if (g_var.str[i] == '<' || g_var.str[i] == '>' || g_var.str[i] == '|')
		{
			k = parsel_defined(&i, g_var.str[i]);
			if (k == 1)
				return (1);
		}
	//	else
	//		undefined_parsel(&i);
		i++;
	}
	return (0);
}

int	parsel_defined(int *i, char c)
{
	int k;

	k = *i;
	if (g_var.str[k + 1] == c && g_var.str[k + 1] != '|')
		i++;
	else if (g_var.str[k] == '|' && g_var.str[k + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_var.exit_code = 258;
		return (1);
	}
	return (0);
}

//void	undefined_parsel(int *i)
//{


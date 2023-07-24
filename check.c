#include "minishell.h"

int	check_quote(char *str)
{
	int	i;
	char c;
	int flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
		{
			c = str[i++];
			flag = 1;
			while (str[i] && str[i] != c)
				i++;
			if (flag == 1 && str[i] != c)
			{
				printf("minishell: syntax error token `%c'\n", c);
				g_var.exit_code = 258;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
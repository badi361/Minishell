#include "minishell.h"

char	*add_quote_v2(char *str)
{
	char *result;
	int	i;
	int	l;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 3));
	while (str[i] != '=')
	{
		result[i] = str[i];
		i++;
	}
	l = i;
	result[i++] = '=';
	result[i++] = '"';
	while (str[l])
	{
		result[i] = str[l];
		l++;
		i++;
	}
	result[i++] = '"';
	result[i] = '\0';
	return (result);
}

int	find_equal_v2(char *str)
{
	int	i;
	int flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (0);
	else
		return (1);
}
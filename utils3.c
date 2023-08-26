#include "minishell.h"

int	ft_strlen_v3(char *s, char c)
{
	int	i;
    int k;

    k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			k++;
		i++;
	}
	k++;
	return (k);
}

int	find_path(char *str)
{
	int	i;
	int	k;
	int	size;
	int	flag;

	flag = 0;
	i = 0;
	size = ft_strlen(str);
	while (g_var.env[i])
	{
		k = 0;
		while (g_var.env[i][k] == str[k] && k < size)
			k++;
		if (k == size)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 1)
		return (i);
	else
		return (-1);
}

int	str_is_digit(char *str)
{
	int	i;
	int k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			k++;
		i++;
	}
	if ((size_t)k == ft_strlen(str))
		return (1);
	return (0);
}

char	*find_equal(char *str)
{
	int	size;
	char *result;
	int	i;

	size = 0;
	i = 0;
	while (str[size] != '=' && str[size])
		size++;
	if (str[size] == '=')
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

int	find_path_v2(char *str)
{
	int	i;
	int	k;
	int	size;
	int	flag;

	flag = 0;
	i = -1;
	size = ft_strlen(str);
	if (str[size - 1] == '=')
		size--;
	while (g_var.export[++i])
	{
		k = 0;
		while (g_var.export[i][k] == str[k] && k < size)
			k++;
		if (k == size)
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 1)
		return (i);
	else
		return (-1);
}

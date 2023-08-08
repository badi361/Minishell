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

	i = 0;
	size = ft_strlen(str);
	while (g_var.env[i])
	{
		k = 0;
		while (g_var.env[i][k] == str[k] && k < size)
		{
			k++;
		}
		if (k == size)
			break ;
		i++;
	}
	return (i);
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
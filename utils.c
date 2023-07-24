#include "minishell.h"

int	ft_strlen_v1(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
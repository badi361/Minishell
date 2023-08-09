#include "minishell.h"

int	agree_cmd_v2(char *str, int size)
{
	if (ft_strncmp_v3(str, "exit", size) == 0)
		return (4);
	else if (ft_strncmp_v3(str, "exit", 4) == 0)
	{
		print_error(str);
		return (-1);
	}
	if (ft_strncmp_v3(str, "env", size) == 0)
		return (5);
	else if (ft_strncmp_v3(str, "env", 3) == 0)
	{
		print_error(str);
		return (-1);
	}
	if (ft_strncmp_v3(str, "cd", size) == 0)
		return (6);
	else if (ft_strncmp_v3(str, "cd", 2) == 0)
	{
		print_error(str);
		return (-1);
	}
	return(agree_cmd_v3(str, size));
}

int	agree_cmd_v3(char *str, int size)
{
	if (ft_strncmp_v3(str, "export", size) == 0)
		return (7);
	else if (ft_strncmp_v3(str, "export", 6) == 0)
	{
		print_error(str);
		return (-1);
	}
	if (ft_strncmp_v3(str, "unset", size) == 0)
		return (8);
	else if (ft_strncmp_v3(str, "unset", 5) == 0)
	{
		print_error(str);
		return (-1);
	}
	return (0);
}
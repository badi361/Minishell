#include "minishell.h"

void	lexer(t_list *list)
{
	list->size = ft_strlen(list->str);
	list->trimmed = ft_strtrim(list->str, " ");
	if (!ft_strlen(list->trimmed))
		return ;
	list->meta_size = size_of_cmd(list->trimmed);
	list->meta_size = list->meta_size + size_of_cmd2(list->str, list);
}

int	size_of_cmd(char *str)
{
	int	i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		is_defined_cmd(str, &counter, &i);
		if (str[i] == ' ')
		{
			while (str[i] == ' ' && str[i])
				i++;
		}
	}
	return (counter);
}

void	is_defined_cmd(char *str, int *counter, int *i)
{
	if (metachars(str[*i]))
	{
		*counter += 1;
		pass_text(str, i);
	}
	if (is_that(str[*i]))
	{
		*i += 1;
		*counter += 1;
		while (is_that(str[*i]) && str[*i] != '\0')
		{
			if (is_that(str[*i]))
			{
				*i += 1;
				break;
			}
		}
	}
}

void	pass_text(char *str, int *i)
{
	int counter;

	while (metachars(str[*i]) && str[*i] != '\0')
	{
		counter = 0;
		while (str[*i] != '\0')
		{
			if (str[*i] == '"' || str[*i] == '\'')
			{
				counter += 1;
				*i += 1;
			}
			if (counter == 2)
				break;
			*i += 1;
		}
		if (str[*i] != '\0')
			*i += 1;
	}
}
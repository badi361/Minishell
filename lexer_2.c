#include "minishell.h"

int	size_of_cmd2(char *str, t_list *list)
{
	int	i;
	int	counter;
	int flag;

	i = 0;
	counter = 0;
	while (str[i])
	{
		flag = 0;
		search_quotations(str, list, i);
		search_s_quote(str, list, i);
		if (i >= list->start_of_quote && i <= list->end_of_quote)
		{
			while (i >= list->start_of_quote && i <= list->end_of_quote)
				i++;
			counter += 1;
			flag = 1;
		}
		else if (is_that(str[i]) && (i < list->start_of_quote))
		{
			i++;
			flag = 1;
		}
		if (i >= list->start_of_quotation && i <= list->end_of_quotation)
		{
			while (i >= list->start_of_quotation && i <= list->end_of_quotation)
				i++;
			counter += 1;
			flag = 1;
		}
		else if (is_that(str[i]) && (i < list->start_of_quotation))
		{
			i++;
			flag = 1;
		}
		if (str[i] == ' ' && flag == 0)
			counter += 1;
		i++;
	}
	return (counter);
}
void	search_quotations(char *str, t_list *list, int i)
{
	int	flag;

	flag = 0;
	list->start_of_quotation = -1;
	list->end_of_quotation = -2;
	while (str[i])
	{
		if (str[i] == '"' && flag == 0)
		{
			list->start_of_quotation = i;
			flag += 1;
		}
		else if (str[i] == '"' && flag == 1)
		{
			list->end_of_quotation = i;
			flag += 1;
		}
		if (flag == 2)
			break;
		i++;
	}
}

void	search_s_quote(char *str, t_list *list, int i)
{
	int	flag;

	flag = 0;
	list->start_of_quote = -1;
	list->end_of_quote = -2;
	while (str[i])
	{
		if (str[i] == '\'' && flag == 0)
		{
			list->start_of_quote = i;
			flag += 1;
		}
		else if (str[i] == '\'' && flag == 1)
		{
			list->end_of_quote = i;
			flag += 1;
		}
		if (flag == 2)
			break;
		i++;
	}
}
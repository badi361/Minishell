#include "minishell.h"

int	size_of_cmd2(char *str, t_list *list)
{
	int	i;
	int	counter;
	int flag;
	int	k;

	k = -1;
	i = 0;
	counter = 0;
	while (str[i])// quotation yaptım gibi. quote içinde uygula
	{
		flag = 0;
		search_quotations(str, list, i);
		search_s_quote(str, list, i);
		if (list->start_of_quotation != -1 && list->end_of_quotation != -2 && str[list->start_of_quotation - 1] != ' ')
		{
			k = list->start_of_quotation;
			while (str[k] != ' ')
				k--;
			k++;
		}
		if (k == i)
		{
			i = pass(str, list, i, k);
			counter += 1;
		}
		if (i >= list->start_of_quote && i <= list->end_of_quote)
		{
			while (i >= list->start_of_quote && i <= list->end_of_quote)
				i++;
			counter += 1;
		}
		else if (is_that(str[i]) && (i < list->start_of_quote || i > list->end_of_quote) && str[i - 1] == ' ')
		{
			i++;
			if (is_that(str[i]))
				i++;
			if (str[i] == ' ')
			{
				while (str[i + 1] == ' ')
					i++;
			}
			flag = 1;
		}
		if (i >= list->start_of_quotation && i <= list->end_of_quotation)
		{
			while (i >= list->start_of_quotation && i <= list->end_of_quotation)
				i++;
			counter += 1;
		}
		else if (is_that(str[i]) && (i < list->start_of_quotation || i > list->end_of_quotation) && (str[i - 1] == ' ' || i == 0))
		{
			i++;
			if (is_that(str[i]))
				i++;
			if (str[i] == ' ')
			{
				while (str[i] == ' ')
					i++;
			}
			flag = 1;
		}
		if (list->start_of_quotation != -1 && list->end_of_quotation != -2 && str[list->end_of_quotation + 1] != ' ')
		{
			k = list->end_of_quotation;
			while (str[k] != ' ')
				k++;
			k--;
		}	
		if (i == list->end_of_quotation + 1 && str[list->end_of_quotation + 1] != ' ')
		{
			i = pass2(str, list, i);
			counter += 1;
		}
		if (str[i] == ' ' && flag == 0)
		{
			while (str[i] == ' ')
				i++;
			counter += 1;
			i--;
		}
		i++;
	}
	i = ft_strlen(str) - 1;
	if (is_that(str[i]))
	{
		i--;
		if (is_that(str[i]))
		{
			i--;
			if (str[i] == ' ')
				counter -= 1;
		}
		else if (str[i] == ' ')
			counter -= 1;
	}
	printf("%db\n", counter);
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

int	pass(char *str, t_list *list, int i, int k)
{
	while (i <= k)
		i++;
	return (i);
}

int pass2(char *str, t_list *list, int i)
{
	while (str[i] != ' ' && str[i])
		i++;
	return (i);
}
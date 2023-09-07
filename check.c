#include "minishell.h"

int	check_quote(char *str) // tırnak açıldığında kapanması da lazım bunu kontrol ediyorum.
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

int	rdr_pipe_check(void)
{
	link_list *tmp;

	tmp = g_var.list;
	if (tmp == NULL)
		return (0);
	if (tmp->flag == '<' || tmp->flag == '>')
		if (tmp->next == NULL)
			return (rdr_pipe_return());
	if (tmp->content[0] == '<' || tmp->content[0] == '>')
		if (tmp->next != NULL)
			if (tmp->next->content[0] == '|')
				return (rdr_pipe_return_v2("|"));
	if (tmp->content[0] == '<' && tmp->content[1] == '<')
		if (tmp->next == NULL)
			return (rdr_pipe_return());
	if (tmp->content[0] == '>' && tmp->content[1] == '>')
		if (tmp->next == NULL)
			return (rdr_pipe_return());
	if (tmp->flag == '<' && tmp->next->content[0] == '<' && tmp->next->content[1] == '\0')
		return (rdr_pipe_return_v2("<"));
	if (tmp->flag == '>' && tmp->next->content[0] == '>' && tmp->next->content[1] == '\0')
		return (rdr_pipe_return_v2(">"));
	if (tmp->flag == '<' && tmp->next->content[0] == '>' && tmp->next->content[1] == '\0')
		return (rdr_pipe_return_v2(">"));
	if (tmp->flag == '>' && tmp->next->content[0] == '<' && tmp->next->content[1] == '\0')
		return (rdr_pipe_return_v2("<"));
	return (0);
}


int	rdr_pipe_check_v3(void) // hata kontrolleri
{
	link_list *tmp;
	tmp = g_var.list;
	if (!tmp)
		return 0;
	printf("\n");
	if (tmp)
		if (tmp->flag == '|')
			return (rdr_pipe_return_v2("|"));
		if ((tmp->flag == '<' || tmp->flag == '>' ) && (tmp->next->flag == '>' || tmp->next->flag == '<'))
			if (tmp->next->content[0] == '<' && tmp->next->content[1] == '<' && tmp->next->content[2] == '\0')
				return (rdr_pipe_return_v2("<<"));
			if (tmp->next->content[0] == '<' && tmp->next->content[1] == '<' && tmp->next->content[2] == '<')
				return (rdr_pipe_return_v2("<<<"));
			if (tmp->next->content[0] == '>' && tmp->next->content[1] == '>')
				return (rdr_pipe_return_v2(">>"));
			if (tmp->next->content[0] == '<' && tmp->next->next->content[0] == '>')
				return (rdr_pipe_return_v2("<>"));
			if (tmp->next->content[0] == '>' && tmp->next->next->content[0] == '<')
				return (rdr_pipe_return_v2("><"));
	return (0);
}


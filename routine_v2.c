#include "minishell.h"

int	get_commands(void)
{
	int			i;
	link_list 	*tmp;

	tmp = g_var.list;
	i = 0;
	g_var.list_size = link_lstsize(g_var.list);
	g_var.array = malloc(sizeof(char *) * (g_var.list_size + 1));
	while (tmp)
	{
		g_var.array[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	g_var.array[i] = NULL;
	if (g_var.array[--i][0] == '|')
		return (rdr_pipe_return_v2('|'));
	return (0);
}

int	link_lstsize(link_list *lst)
{
	int			i;
	link_list	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	rdr_pipe_return_v2(char c)
{
	printf("minishell: syntax error near unexpected token `%c'\n", c);
	g_var.exit_code = 258;
	return (1);
}
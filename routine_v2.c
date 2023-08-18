#include "minishell.h"

int	get_commands(void) // terminalden girilen komutları array imin içinde atıyorum.
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
	tmp = g_var.list;
	if (tmp == NULL)
		return (1);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->flag == '|')
			return (rdr_pipe_return_v2('|'));
	}
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

void	rdr_flag(void) // > ndan sonraki verinin flagini i yani input, < dan sonraki verinin flagini o yani output yapıyorum
{
	link_list *tmp;

	tmp = g_var.list;
	while (tmp)
	{
		if (tmp->content[0] == '>' && tmp->content[1] == '\0')
			if (tmp->next)
				tmp->next->flag = 'o';
		if (tmp->content[0] == '<' && tmp->content[1] == '\0')
			if (tmp->next)
				tmp->next->flag = 'i';
		if (tmp->content[0] == '>' && tmp->content[1] == '>')
			if (tmp->next)
				tmp->next->flag = 'r';
		if (tmp->content[0] == '<' && tmp->content[1] == '<')
			if (tmp->next)
				tmp->next->flag = 'h';
		tmp = tmp->next;
	}
}

void	cmd_init(void) // terminalden a >> b | b < a gibi bir komut geldiyse pipedan önceki veriyinin sonucu pipe dan sonrasına atmam lazım bu yüzden 3 boyutlu bir dizi oluşturup pipe ları böldüm.
{
	int			i;

	i = 0;
	cmd_init_help();
	g_var.cmds = NULL;
	g_var.cmds = malloc(sizeof(pipe_list *) * (g_var.pipe_count + 2));
	while (i <= g_var.pipe_count)
	{
		g_var.cmds[i] = malloc(sizeof(pipe_list));
		g_var.cmds[i]->str = g_var.string_3[i];
		g_var.cmds[i]->f_in = STDIN_FILENO;
		g_var.cmds[i]->f_out = STDOUT_FILENO;
		g_var.cmds[i]->rdr_fl = 0;
		i++;
	}
	g_var.cmds[i] = NULL;
}
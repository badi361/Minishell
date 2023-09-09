/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:36:03 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 18:37:38 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(void)
{
	t_list	*tmp;

	tmp = g_var.list;
	if (tmp == NULL)
		return (1);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->flag == '|')
			return (rdr_pipe_return_v2("|"));
	}
	return (0);
}

int	rdr_pipe_return_v2(char *c)
{
	printf("minishell: syntax error near unexpected token `%s'\n", c);
	g_var.exit_code = 258;
	return (1);
}

void	rdr_flag(void)
{
	t_list	*tmp;

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

void	cmd_init(void)
{
	int			i;

	i = 0;
	cmd_init_help();
	g_var.cmds = NULL;
	g_var.cmds = malloc(sizeof(t_pipe_list *) * (g_var.pipe_count + 2));
	while (i <= g_var.pipe_count)
	{
		g_var.cmds[i] = malloc(sizeof(t_pipe_list));
		g_var.cmds[i]->str = g_var.string_3[i];
		g_var.cmds[i]->f_in = STDIN_FILENO;
		g_var.cmds[i]->f_out = STDOUT_FILENO;
		i++;
	}
	g_var.cmds[i] = NULL;
}

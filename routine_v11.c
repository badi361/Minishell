/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:26:22 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/10 15:07:44 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_error(int fd, char *str)
{
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", str);
		g_var.exit_code = 1;
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s'\n", str);
		g_var.exit_code = 258;
	}
}

void	no_such(char *str)
{
	printf("minishell: %s: No such file or directory\n", str);
	g_var.exit_code = 127;
}

int	rdr_init_help(t_list *tmp, int *k, int fd)
{
	if (tmp->flag == 'r')
	{
		fd = open(tmp->content, O_CREAT | O_APPEND | O_RDWR, 0777);
		g_var.cmds[*k]->f_out = fd;
	}
	if (tmp->flag == 'h')
		ft_here_doc(tmp->content, *k);
	if (tmp->flag == '|')
		*k += 1;
	if (fd == -1)
	{
		g_var.cmds[*k]->f_out = -1;
		fd_error(fd, tmp->content);
		return (1);
	}
	return (0);
}

int	rdr_pipe_ctrl(t_list *tmp)
{
	if (tmp->content[0] == '<' && tmp->content[1] == '\0'
		&& tmp->next->content[0] == '>' && tmp->next->content[1] == '\0')
	{
		tmp = tmp->next;
		if (tmp->next != NULL)
		{
			if (tmp->next->flag == '<' || tmp->next->flag == '>')
				return (rdr_pipe_return_v2(tmp->next->content));
		}
		else
			return (rdr_pipe_return());
	}
	if (tmp->content[0] == '<' || tmp->content[1] == '<')
		if (tmp->next != NULL)
			if (tmp->next->flag == '<' || tmp->next->flag == '>')
				return (rdr_pipe_return_v2(tmp->next->content));
	if (rdr_pipe_ctrl_v2(tmp))
		return (1);
	return (0);
}

int	rdr_pipe_ctrl_v2(t_list *tmp)
{
	if (tmp->content[0] == '>' && tmp->content[1] == '\0'
		&& tmp->next->content[0] == '<' && tmp->next->content[1] == '\0')
	{
		tmp = tmp->next;
		if (tmp->next != NULL)
		{
			if (tmp->next->flag == '<' || tmp->next->flag == '>')
				return (rdr_pipe_return_v2(tmp->next->content));
			else
				return (rdr_pipe_return());
		}
	}
	return (0);
}

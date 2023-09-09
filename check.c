/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:43:59 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 21:14:14 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	int		i;
	char	c;
	int		flag;

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
	t_list	*tmp;

	tmp = g_var.list;
	if (!tmp)
		return (1);
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
	if (rdr_pipe_ctrl(tmp) != 0)
		return (1);
	return (0);
}

int	rdr_pipe_check_v3(void)
{
	t_list	*tmp;

	tmp = g_var.list;
	if (tmp)
		if (tmp->flag == '|')
			return (rdr_pipe_return_v2("|"));
	while (tmp)
	{
		if (tmp->flag == '<')
		{
			if (tmp->next != NULL)
			{
				if (tmp->next->flag == '>' || tmp->next->flag == '<')
					return (rdr_pipe_return_v2("<"));
			}
			else
				return (rdr_pipe_return());
		}
		if (rdr_pipe_check_v4(tmp) != 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	rdr_pipe_check_v4(t_list *tmp)
{
	if (tmp->flag == '>')
	{
		if (tmp->next != NULL)
		{
			if (tmp->next->flag == '<' || tmp->next->flag == '>')
				return (rdr_pipe_return_v2(">"));
		}
		else
			return (rdr_pipe_return());
	}
	return (0);
}

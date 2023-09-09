/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:37:57 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 18:39:33 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_init_help(void)
{
	t_list		*tmp;
	int			i;

	tmp = g_var.list;
	i = 0;
	pipe_init();
	g_var.string_3 = malloc(sizeof(char **) * (g_var.pipe_count + 2));
	while (tmp)
	{
		g_var.string_3[i] = malloc(sizeof(char *) * (arg_count() + 2));
		get_arg(&i, &tmp);
		i++;
	}
	g_var.string_3[i] = NULL;
}

void	pipe_init(void)
{
	t_list		*tmp;
	int			len;
	int			i;

	i = 0;
	len = 0;
	tmp = g_var.list;
	while (tmp)
	{
		if (tmp->flag == '|')
			len++;
		tmp = tmp->next;
	}
	g_var.pipe_count = len;
	g_var.pipe = malloc(sizeof(int *) * len);
	while (i < len)
	{
		g_var.pipe[i] = malloc(sizeof(int) * 2);
		pipe(g_var.pipe[i]);
		i++;
	}
	g_var.pid = malloc(sizeof(pid_t) * (len + 1));
}

int	arg_count(void)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = g_var.list;
	while (tmp)
	{
		if (tmp->flag == 'b')
			len++;
		if (tmp->flag == '|')
			break ;
		tmp = tmp->next;
	}
	return (len);
}

void	get_arg(int	*k, t_list **tmp)
{
	int	i;

	i = 0;
	while (*tmp)
	{
		if ((*tmp)->flag == 'b')
		{
			g_var.string_3[*k][i] = ft_strdup((*tmp)->content);
			i++;
		}
		if ((*tmp)->flag == '|')
			break ;
		(*tmp) = (*tmp)->next;
	}
	g_var.string_3[*k][i] = 0;
	if ((*tmp))
		if ((*tmp)->flag == '|')
			(*tmp) = (*tmp)->next;
}

void	input_to_place(void)
{
	int	i;

	i = 0;
	while (i < g_var.pipe_count)
	{
		g_var.cmds[i]->f_out = g_var.pipe[i][1];
		i++;
	}
	i = 1;
	while (i < (g_var.pipe_count + 1))
	{
		g_var.cmds[i]->f_in = g_var.pipe[i - 1][0];
		i++;
	}
}

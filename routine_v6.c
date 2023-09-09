/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_v6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:40:33 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 20:10:15 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(void)
{
	int	i;
	int	k;

	k = 0;
	while (g_var.export[k])
	{
		printf("declare -x ");
		i = 0;
		while (g_var.export[k][i])
		{
			if (g_var.export[k][i] != '=')
				printf("%c", g_var.export[k][i]);
			else
			{
				printf("=%c", '"');
				printf("%s", &g_var.export[k][++i]);
				printf("%c", '"');
				break ;
			}
			i++;
		}
		printf("\n");
		k++;
	}
}

void	ft_export(int k)
{
	int		i;
	char	*str;

	i = 0;
	while (g_var.cmds[++k])
	{
		while (g_var.cmds[k]->str[++i])
		{
			if (ft_isalpha(g_var.cmds[k]->str[i][0]))
			{
				str = find_equal(g_var.cmds[k]->str[i]);
				if (find_equal_v2(g_var.cmds[k]->str[i]))
				{
					new_export(find_path_v2(str), k, i);
					new_env(find_path(str), k, i);
				}
				else
					new_export(find_path_v2(str), k, i);
				free(str);
			}
			else
				printf("minishell: export: %s: not a valid identifier\n",
					g_var.cmds[0]->str[i]);
		}
	}
}

void	new_export(int index, int k, int l)
{
	int		i;
	char	**str;

	i = 0;
	if (index == -1)
	{
		str = malloc(sizeof(char *) * (g_var.export_size + 2));
		while (g_var.export[i])
		{
			str[i] = ft_strdup(g_var.export[i]);
			free(g_var.export[i]);
			i++;
		}
		str[i++] = ft_strdup(g_var.cmds[k]->str[l]);
		free(g_var.export);
		str[i] = NULL;
		g_var.export = str;
		g_var.export_size += 1;
	}
	else if (find_equal_v2(g_var.cmds[k]->str[l]))
	{
		free(g_var.export[index]);
		g_var.export[index] = ft_strdup(g_var.cmds[k]->str[l]);
	}
}

char	*add_quote(int k, int i)
{
	int		t;
	char	*result;
	int		l;

	t = 0;
	result = malloc(sizeof(char) * (ft_strlen(g_var.cmds[k]->str[i] + 3)));
	while (g_var.cmds[k]->str[i][t] != '=')
	{
		result[t] = g_var.cmds[k]->str[i][t];
		t++;
	}
	l = t;
	result[t++] = '=';
	result[t++] = '"';
	while (g_var.cmds[k]->str[i][l])
	{
		result[t] = g_var.cmds[k]->str[i][l];
		t++;
		l++;
	}
	result[t] = '"';
	result[t + 1] = '\0';
	return (result);
}

void	leaks_destroyer_v2(void)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	if (g_var.pipe_count >= 0)
	{
		while (++i < g_var.pipe_count)
			free(g_var.pipe[i]);
		free(g_var.pipe);
	}
	i = -1;
	if (g_var.string_3)
	{
		while (g_var.string_3[++i])
		{
			k = -1;
			while (g_var.string_3[i][++k])
				free(g_var.string_3[i][k]);
			free(g_var.string_3[i]);
		}
		free(g_var.string_3);
	}
}

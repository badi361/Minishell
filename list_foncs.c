/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_foncs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguzel <bguzel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:36:56 by bguzel            #+#    #+#             */
/*   Updated: 2023/09/09 18:16:33 by bguzel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
	{
		return ;
	}
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		link_lstdelone(*lst);
		*lst = tmp;
	}
}

void	link_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	free(lst->content);
	free(lst);
}

void	link_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	link_lstlast(*lst)->next = new;
}

t_list	*link_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_list	*link_lstnew(char *content, char flag)
{
	t_list	*str;

	str = malloc(sizeof(t_list));
	if (!str)
		return (0);
	str->content = content;
	str->flag = flag;
	str->next = NULL;
	return (str);
}

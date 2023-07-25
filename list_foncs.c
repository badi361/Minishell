#include "minishell.h"

void	link_lstclear(link_list **lst)
{
	link_list	*tmp;

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

void	link_lstdelone(link_list *lst)
{
	if (!lst)
		return ;
	free(lst->content);
	free(lst);
}

void	link_lstadd_back(link_list **lst, link_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	link_lstlast(*lst)->next = new;
}

link_list	*link_lstlast(link_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

link_list	*link_lstnew(char *content, char flag)
{
	link_list	*str;

	str = malloc(sizeof(link_list));
	if (!str)
		return (0);
	str->content = content;
	str->flag = flag;
	str->next = NULL;
	return (str);
}
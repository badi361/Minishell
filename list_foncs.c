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
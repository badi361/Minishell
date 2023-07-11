#include "minishell.h"

void	lexer(t_list *list)
{
	list->size = ft_strlen(list->str);
	list->trimmed = ft_strtrim(list->str, " ");
	if (!ft_strlen(list->trimmed))
		return ;
	list->meta_size = size_of_cmd(list->trimmed, list);
	list->holder = malloc(sizeof(char *) * (list->meta_size + 1));
	//post_cmd(list);
}

//void	post_cmd()
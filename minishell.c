#include "minishell.h"

int main (int ac, char **av)
{
	(void)ac;
	(void)av;
    t_list *list;
	list = malloc(sizeof(t_list));
    while (1)
    {
		list->str = readline("minishell: ");
		add_history(list->str);
    	lexer(list);
		printf("%d\n", list->meta_size);
    }
}

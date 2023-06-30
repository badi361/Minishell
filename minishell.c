#include "minishell.h"

int main (int ac, char **av)
{
	if (ac > 1)
	{
    	t_list *list;
		list = malloc(sizeof(t_list));
		int i = 0;
		list->str = ft_strcat(av[1], av[2]);
		list->str = ft_strcat(list->str, av[3]);
		printf("%s\n", list->str);
    	while (1)
    	{
        	lexer(list);
			printf("%d", list->meta_size);
			exit(0);
    	}
	}	
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	dest[i] = ' ';
	i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
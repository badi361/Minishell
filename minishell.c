#include "minishell.h"

int main (int ac, char **av, char **env)
{ 
	
	(void)ac;
	(void)av;
    while (1)
    {
		t_list.str = readline("minishell: ");
		if (t_list.str == NULL)
			break ;
		add_history(t_list.str);
    	lexer();
		if (error_check())
		{
			free(t_list.str);
			continue;
		}
    }
	//a>>b yazınca hepsini bir stringe alıyo düzelt a >> b ayrı ayrı almalı
}

int	error_check()
{
	link_list *tmp;
	tmp = t_list.lst;
	while (tmp)
	{
		if (tmp->flag == '<' || tmp->flag == '>')
		{
			if (tmp->next == NULL)
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				return(1);
			}
		}
		if (tmp->content[0] == '>' && tmp->content[1] == '>')
		{
			if (tmp->next == NULL)
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				return(1);				
			}
		}
		if (tmp->content[0] == '<' && tmp->content[1] == '<')
		{
			if (tmp->next == NULL)
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				return(1);				
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	malloc_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	t_list.env_size = i;
	t_list.env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		t_list.env[i] = ft_strdup(env[i]);
		i++;
	}
	t_list.env[i] = NULL;
}
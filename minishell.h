#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct z_list
{
    char	*content;
	struct z_list *next;
	char	flag;	
}			link_list;

struct s_var
{
	char		**env;
	int			env_size;
	link_list 	*list;
	char		*str;
	int			exit_code;
}	g_var;

void	malloc_env(char **env);
int		routine(char *str);
int		lexer_parsel(char *str);
void	link_lstclear(link_list **lst);
void	link_lstdelone(link_list *lst);
int		check_quote(char *str);
int		parsel_defined(int *i, char c);
int		ft_strlen_v1(const char *s);
#endif
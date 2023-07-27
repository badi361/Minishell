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
	int			dolarflag;
	int			list_size;
	char		**array;
}	g_var;

void		malloc_env(char **env);
int			routine(char *str);
int			lexer_parsel(char *str);
void		link_lstclear(link_list **lst);
void		link_lstdelone(link_list *lst);
int			check_quote(char *str);
int			parsel_defined(int *i, char c);
int			ft_strlen_v1(const char *s);
char		*ft_strdup_v2(char *str, int start, int end);
void		link_lstadd_back(link_list **lst, link_list *new);
link_list	*link_lstlast(link_list *lst);
link_list	*link_lstnew(char *content, char flag);
int			is_it_special(char c);
char		*ft_strjoin_v3(char *s1, char *s2);
char		*ft_strdup_v3(char *str, int *start, char end);
void		dollar_help(int i);
char		*only_dolar(void);
int			ft_strncmp_v3(const char *s1, const char *s2, size_t n);
char		*handle_regular(char *str, int *index);
void		undefined_parsel(int *i);
char		*get_dolar(char *str, char c);
char		*get_env_var(char *str, int *i, int *j, char **env);
int			ft_strlen_v2(char *str, char q, int i);
int			rdr_pipe_return(void);
int			rdr_pipe_check(void);
int			rdr_pipe_check_v2(void);
int			rdr_pipe_return_v2(char c);
int			rdr_pipe_check_v3(void);
int			link_lstsize(link_list *lst);
int			get_commands(void);
#endif
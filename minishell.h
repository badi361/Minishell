#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <unistd.h>

typedef struct z_list
{
	char 	*content;
	char	flag;
	struct z_list *next;
}			link_list;

struct s_list
{
    int	size;
	char *str;
	char *trimmed;
	int	meta_size;
	char *holder;
	char parsel_flag;
	link_list *lst;
	int	env_size;
	char **env;
}   t_list;

int			ft_strlen(char *str);
char		*ft_strtrim(char *s1, char *set);
int			metachars(char a);
int			is_that(char a);
void		lexer();
char		*ft_substr(char *s, int start, int len);
char		*ft_strchr(char *s, int c);
char		*ft_strdup(char *s1);
link_list	*link_lstnew(char *content, char flag);
void		link_lstadd_back(link_list **lst, link_list *new);
link_list	*link_lstlast(link_list *lst);
void		link_lstclear(link_list **lst);
void		link_lstdelone(link_list *lst);
void		f_parsel(char *line, int *i);
int			error_check();
void		malloc_env(char **env);

#endif
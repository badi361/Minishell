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

typedef struct s_list
{
    int	size;
	char *str;
	char *trimmed;
	int	meta_size;
	char **holder;
	int	start_of_quotation;
	int	end_of_quotation;
	int	start_of_quote;
	int	end_of_quote;
}   t_list;

int		ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
int		metachars(char a);
int		is_that(char a);
int		size_of_cmd(char *str, t_list *list);
void	lexer(t_list *list);
void	search_quotations(char *str, t_list *list, int i);
void	search_s_quote(char *str, t_list *list, int i);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
int		pass(char *str, t_list *list, int i, int k);
int		pass2(char *str, t_list *list, int i);
#endif
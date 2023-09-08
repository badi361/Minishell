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

typedef struct pipe_var
{
	char 	**str;
	int		f_in;
	int		f_out;

}			pipe_list;

struct s_var
{
	int			export_size;
	char		**export;
	int			nl_flag;
	pid_t		*pid;
	pipe_list	**cmds;
	char		**env;
	char		**env_path;
	int			env_size;
	link_list 	*list;
	char		*str;
	int			exit_code;
	int			pipe_count;
	int			**pipe;
	char		***string_3;
	char		*path;
	int			hd_flag;
	int			exit;
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
int			rdr_pipe_return_v2(char *c);
int			rdr_pipe_check_v3(void);
int			pipe_check(void);
void		rdr_flag(void);
void		pipe_init(void);
int			arg_count(void);
void		cmd_init_help(void);
void		get_arg(int	*k, link_list **tmp);
void		cmd_init(void);
void		input_to_place(void);
int			ft_strlen_v3(char *s, char c);
int			find_path(char *str);
int			split_env(void);
void		search_on_env(int k, int t);
int			agree_cmd(char *str, int i);
void		search_cmd(void);
void		ft_echo(int	i);
int			just_echo(int i);
int			pass_nl(int k);
int			str_is_digit(char *str);
void		ft_exit(int	i);
void		ft_env(void);
void		ft_pwd(void);
void		ft_cd(int k);
void		cd_back(char *str);
void		print_error(char *str);
void		cd_tilde(char *str);
int			malloc_path(int i, char *str);
void		cd_next(char *str, char *next);
void		print_export(void);
void		ft_export(int k);
char		*find_equal(char *str);
char		*add_quote_v2(char *str);
int			find_equal_v2(char *str);
void		new_export(int index, int k, int l);
char		*add_quote(int k, int i);
void		new_env(int	index, int k, int l);
int			find_path_v2(char *str);
void		search_cmd_v2(int result, int i);
void		refresh_env(int index);
void		refresh_export(int index);
void		ft_unset(int i);
char		*find_equal_v3(char *str);
int			find_on_env(int i, int k);
int			find_on_export(int i, int k);
void		rdr_init(void);
void		dup_func(int i);
void		close_fd(void);
void		ft_here_doc(char *data, int k);
void		write_on_fd(char *str, int fd);
void		unlink_to_hd(void);
void		close_fd_2(pipe_list *cmds);
void		leaks_destroyer(void);
void		leaks_destroyer_v2(void);
void		signal_handle(int signal);
void		cd_helper(char *str);
void		cd_helper_v2(char *str);
void		fd_error(int fd, char *str);
int			ft_strcmp(char *s1, char *s2);
void		no_such(char *str);
#endif
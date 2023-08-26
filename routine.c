#include "minishell.h"

int	lexer_parsel(char *str) // < > | ysa ayrı bunlar değilse ayrı listelere atıyorum. parsel defined fonksiyonuna girmeyenlerin flagini 'b' yapıyorum
{
	int i;

	i = 0;
	g_var.str = ft_strtrim(str, " ");
	link_lstclear(&g_var.list);
	while (i < ft_strlen_v1(g_var.str))
	{
		while (g_var.str[i] == ' ' || g_var.str[i] == 9)
			i++;
		if (g_var.str[i] == '<' || g_var.str[i] == '>' || g_var.str[i] == '|')
		{
			if (parsel_defined(&i, g_var.str[i]))
				return (1);
		}
		else if (g_var.str[i] && g_var.str[i] != ' ' && g_var.str[i] != 9)
			undefined_parsel(&i);
	}
	return (0);
}

int	parsel_defined(int *i, char c)
{
	int		k;
	char	*str;
	int		l;

	k = 1;
	l = *i;
	if (g_var.str[l + k] == c && g_var.str[l + k] != '|')
		k += 1;
	else if (g_var.str[l] == '|' && g_var.str[l + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_var.exit_code = 258;
		return (1);
	}
	str = ft_strdup_v2(g_var.str, l, l + k);
	link_lstadd_back(&g_var.list, link_lstnew(str, c));
	*i = k + l;
	return (0);
}

void	undefined_parsel(int *i) // önce tırnak içinde mi kontrol ediyorum. sonrasında dolar var mı eğer varsa dolardan sonra yazılanın karşılığını env tan alıyorum. 
{
	int	k;
	char *result;

	result = NULL;
	k = *i;
	while (g_var.str[k] && !is_it_special(g_var.str[k]))
	{
		if (g_var.str[k] == 34 || g_var.str[k] == 39)
		{
			k++;
			result = ft_strjoin_v3(result, get_dolar
					(ft_strdup_v3(g_var.str, &k, g_var.str[k - 1]), g_var.str[k - 1]));
		}
		else
			result = ft_strjoin_v3(result,
					get_dolar(handle_regular(g_var.str, &k), 0));
	}
	link_lstadd_back(&g_var.list, link_lstnew(result, 'b'));
	*i = k;
}

char	*get_dolar(char *str, char c)
{
	char 	*result;
	char	*env;
	int		i;
	int		j;
	if (c == 39)
		return (str);
	i = 0;
	result = NULL;
	while (str[i])
	{
		j = i;
		while (str[i] != '$' && str[i])
			i++;
		result = ft_strjoin_v3(result, ft_strdup_v2(str, j, i));
		if (str[i] == '$')
		{
			i++;
			while (str[i] == '$')
				i++;
			env = get_env_var(&str[i], &i, &j, g_var.env);
			if (env)
				result = ft_strjoin_v3(result, env);
		}
	}
	free(str);
	return (result);
}

char	*get_env_var(char *str, int *i, int *j, char **env)
{
	int	len;
	int	k;

	k = 0;
	if (str[k] == '\0')
		return (only_dolar());
	if (str[k] == '?')
	{
		*i += 1;
		return (ft_itoa(g_var.exit_code));
	}
	while (ft_isalnum(str[k]))
		k++;
	*j = *i;
	*i += k;
	len = *i - *j;
	while (*env)
	{
		if (ft_strncmp_v3(&str[0], *env, len) == 0 && (*env)[len] == '=')
			break ;
		env++;
	}
	if (!(*env))
		return (NULL);
	return (ft_strdup(&((*env)[len + 1])));
}
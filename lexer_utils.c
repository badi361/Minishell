#include "minishell.h"

int	metachars(char a)
{
	if (a != '<' && a != '>' && a != ' ' && a != '&' && a != '|')
		return (1);
	return (0);
}

int	is_that(char a)
{
	if (a == '<' || a == '>' || a == '|' || a == '&')
		return (1);
	return (0);
}
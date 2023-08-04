#include "minishell.h"

void	split_env(void)
{
	int i;
    int	k;
	char **str;
	int	t;

	i = 0;
	k = find_path("PATH=");
	str = ft_split(&g_var.env[k][5], ':');
	g_var.env_path = (char **)malloc(sizeof(char *) * (ft_strlen_v3(&g_var.env[k][5], ':') + 1));
	while (i < ft_strlen_v3(&g_var.env[k][5], ':'))
	{
		t = 0;
		g_var.env_path[i] = malloc(sizeof(char) * ft_strlen(str[i]) + 1);
		while (str[i][t])
		{
			g_var.env_path[i][t] = str[i][t];
			t++;
		}
		free(str[i]);
		g_var.env_path[i][t] = '\0';
		i++;
	}
	free(str);
	g_var.env_path[i] = NULL;
}
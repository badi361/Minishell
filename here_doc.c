#include "minishell.h"

int	ft_here_doc(char *data)
{
    char	*str;
	int 	fd;

	unlink_to_hd();
	g_var.hd_flag = 0;
	fd = open(".temporary", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		str = readline("> ");
		if (!ft_strncmp(str, "> ", ft_strlen(str)))
			write(fd, "\n", 1);
		else if (!ft_strncmp(data, str, ft_strlen(str)))
			break ;
		else
			write_on_fd(str, fd);
		free(str);
	}
	close(fd);
	fd = open(".temporary", O_RDONLY | O_TRUNC, 0777);
	g_var.hd_flag = 1;
	return (fd);
}

void	write_on_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	unlink_to_hd(void)
{
	char *temporary;
	char str[128];

	if (g_var.hd_flag)
	{
		getcwd(str, sizeof(str));
		temporary = ft_strjoin(str, "/.temporary");
		unlink(temporary);
		free(temporary);
	}
}